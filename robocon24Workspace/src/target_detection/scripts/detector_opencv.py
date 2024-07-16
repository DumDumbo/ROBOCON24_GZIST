#!/usr/bin/env python3
# coding=utf-8

"""
/************************************************************************************************
* @FileName: color_Tracking
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/26
* @Description: Track the centroid of the target with the specified color
*************************************************************************************************/
"""

"""-------------------------------------Import Start---------------------------------------------"""
import cv2
import numpy as np
import rospy
from sensor_msgs.msg import Image
from std_msgs.msg import Header, String
from cv_bridge import CvBridge
from ros_stm32_serial.msg import serial_topic_msgs
import threading

class color_select:
    def __init__(self):
        self.hsv_low = np.array([0, 0, 0])
        self.hsv_high = np.array([0, 0, 0])
        cv2.namedWindow('image', cv2.WINDOW_NORMAL | cv2.WINDOW_FREERATIO)
        # H low：
        #    0：指向整数变量的可选指针，该变量的值反映滑块的初始位置。
        #  179：表示滑块可以达到的最大位置的值为179，最小位置始终为0。
        # h_low：指向每次滑块更改位置时要调用的函数的指针，指针指向h_low元组，有默认值0。

        cv2.createTrackbar('H low', 'image', 0, 179, self.h_low)
        cv2.createTrackbar('H high', 'image', 0, 179, self.h_high)
        cv2.createTrackbar('S low', 'image', 0, 255, self.s_low)
        cv2.createTrackbar('S high', 'image', 0, 255, self.s_high)
        cv2.createTrackbar('V low', 'image', 0, 255, self.v_low)
        cv2.createTrackbar('V high', 'image', 0, 255, self.v_high)
    
    def h_low(self, value):
        self.hsv_low[0] = value

    def h_high(self, value):
        self.hsv_high[0] = value

    def s_low(self, value):
        self.hsv_low[1] = value

    def s_high(self, value):
        self.hsv_high[1] = value

    def v_low(self, value):
        self.hsv_low[2] = value

    def v_high(self, value):
        self.hsv_high[2] = value

    
    """*****************************************************
    *@FunctionName: rgb2Hsv(img):
    *@Parameter:    img
    *@Description:  ½«RGBÍ¼Ïñ×ª»»ÎªHSVÍ¼Ïñ¸ñÊ½
    *@ReturnVal:    HSVÍ¼Ïñ¸ñÊ½
    *****************************************************"""
    def rgb2Hsv(self, img):
        roi = img[0:120, 110:210]
        imgGB = cv2.GaussianBlur(img, (3,3),0)
        hsv_img = cv2.cvtColor(imgGB, cv2.COLOR_BGR2HSV)
        erode_hsv = cv2.erode(hsv_img, None, iterations=2)
        dilated_hsv= cv2.dilate(erode_hsv, None, iterations=2)
        return dilated_hsv


    """*****************************************************
    *@FunctionName: imageFromRosCallback():
    *@Parameter:    None
    *@Description:  Astra S Í¼Ïñ»°Ìâ»Øµ÷º¯Êý
    *@ReturnVal:    None
    *****************************************************"""
    def resultShow(self, image):
        hsvImg = self.rgb2Hsv(image)
        dst = cv2.inRange(hsvImg, self.hsv_low, self.hsv_high)  # 阈值判断
        image = image[0:120, 110:210]
        cv2.imshow('dst', dst)
        cv2.imshow("original fram", image)
        cv2.waitKey(1)


class detector_opencv:
    def __init__(self):
        self.bridge = CvBridge()

        # 话题订阅者
        self.colorSub = rospy.Subscriber('/camera_astras/color/image_raw', Image, self.colorCallback)
        self.serialDataSub = rospy.Subscriber('/serial_data', serial_topic_msgs, self.serialCallback)

        # 普通相机
        self.cap = cv2.VideoCapture("/dev/YahboomCamera", cv2.CAP_V4L2)
        # 参数设置
        self.__set_camera_params()
        
        # 用于选择相机输入源（0：普通相机，1：深度相机）
        self.cameraSelect = "0"

        self.Width = 640
        self.Height = 480

        # 颜色阈值
        self.redLower = np.array([158, 80, 76])
        self.redUpper = np.array([179, 255, 255])

        self.blueLower = np.array([104, 103, 124])
        self.blueUpper = np.array([117, 255, 255])

        self.purpleLower = np.array([133, 92, 91])
        self.purpleUpper = np.array([157, 255, 180])

        # 话题发布者
        self.OpenCVImgaePub = rospy.Publisher("/OpencvImage", Image, queue_size =3)
        self.colorStringPub = rospy.Publisher('/color_detected', String, queue_size=3)

        self.header = Header()
        self.robot_status = None
        self.color_detected = "None"

        # self.colorSelect = color_select()

        rospy.logwarn("Initialized")

    def __set_camera_params(self):
        self.cap.set(3, 320) # width
        self.cap.set(4, 240) # height
        self.cap.set(cv2.CAP_PROP_AUTO_WB, 0.0)  # 关闭自动白平衡
        self.cap.set(cv2.CAP_PROP_WB_TEMPERATURE, 4500)  # 手动设置白平衡温度
        self.cap.set(cv2.CAP_PROP_AUTO_EXPOSURE, 1.0)  # 关闭自动曝光
        # self.cap.set(cv2.CAP_PROP_EXPOSURE, 100)  # 手动曝光参数
        self.cap.set(cv2.CAP_PROP_GAIN, 0.0)  #关闭自动增益，设置增益为0


    def __RGB_To_HSV(self, img):
        roi = img[0:120, 110:160]
        imgGB = cv2.GaussianBlur(roi, (3, 3), 0)
        hsv_img = cv2.cvtColor(imgGB, cv2.COLOR_BGR2HSV)
        # cv2.imshow('roi', roi)
        # cv2.waitKey(1)
        return hsv_img

    def __object_detector(self,hsv_frame):
        self.getColor(hsv_frame)
        # 发布消息
        self.colorStringPub.publish(self.color_detected)

    def __detect_color(self, range_img):
        # kernel = np.ones((3, 3), np.uint8)
        # opening_frame = cv2.morphologyEx(src=range_img, op=cv2.MORPH_OPEN, kernel=kernel, iterations=1)
        # closing_frame = cv2.morphologyEx(src=opening_frame, op=cv2.MORPH_CLOSE, kernel=kernel, iterations=2)

        # output_frame = closing_frame.copy()

        Target_list, _ = cv2.findContours(range_img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        if len(Target_list) > 0:
            for i in Target_list:
                x, y, w, h = cv2.boundingRect(i)
                top_left = (x, y)
                bottom_right = (x + w, y + h)
                if w > 25 and h > 25:
                    # cv2.rectangle(original_frame, top_left, bottom_right, color=color, thickness=1)
                    # M = cv2.moments(i)
                    # if M["m00"] != 0:
                    #     Cx = int(M["m10"] / M["m00"])
                    #     Cy = int(M["m01"] / M["m00"])

                        # cv2.line(original_frame, (320, 0), (320, 480), color=(0, 255, 0))
                        # cv2.line(original_frame, (0, 240), (640, 240), color=(0, 255, 0))
                        # cv2.circle(original_frame, (Cx, Cy), 5, color, -1)
                        return True
        return False

    def getColor(self,input_image):
        # 检测是否为紫色
        purple_range_img = cv2.inRange(input_image, self.purpleLower, self.purpleUpper)
        if self.__detect_color(purple_range_img):
            self.color_detected = "Purple"
            return  # 检测到紫色，退出函数      
          
        # 蓝色检测
        blue_range_img = cv2.inRange(input_image, self.blueLower, self.blueUpper)
        if self.__detect_color(blue_range_img):
            self.color_detected = "Blue"
            return  # 检测到蓝色，退出函数
        
         # 蓝色检测
        red_range_img = cv2.inRange(input_image, self.redLower, self.redUpper)
        if self.__detect_color(red_range_img):
            self.color_detected = "Red"
            return  # 检测到红色，退出函数

        

    def colorCallback(self, msg):
        if self.robot_status == "GrainSearch":
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")
            hsv_image = self.__RGB_To_HSV(cv_image)
            self.__object_detector(hsv_image)
        else:
            pass
    
    def serialCallback(self, msg):
        self.robot_status = msg.RobotStatus

    def task1(self):
        while not rospy.is_shutdown():
            try:
                if self.robot_status == "GrainSearch"  or self.robot_status == "PreGrainSearch" or self.robot_status == "InitialMovementPoint1":
                    if self.cameraSelect == "0":
                        ret, image = self.cap.read()
                        if ret:
                            self.color_detected = "None"
                            # # 进行颜色阈值调试时打开
                            # self.colorSelect.resultShow(image)
                            
                            
                            # self.OpenCVImgaePub.publish(self.bridge.cv2_to_imgmsg(image, encoding="rgb8"))
                            cv2.imshow('image', image)
                            cv2.waitKey(1)
                            hsv_image = self.__RGB_To_HSV(image)
                            self.__object_detector(hsv_image)
                        else:
                            cv2.destroyAllWindows()
                            pass
                else:
                    cv2.destroyAllWindows()
            except KeyboardInterrupt:
                cv2.destroyAllWindows()


    def task2(self):
        while not rospy.is_shutdown():
            try:
                rospy.spin()
            except KeyboardInterrupt:
                rospy.logwarn("detector_opencv exit")


if __name__ == "__main__":
    rospy.init_node('detector_opencv')
    Detection = detector_opencv()
    rospy.logwarn('detector initialized')

    thread1 = threading.Thread(target = Detection.task1())
    thread2 = threading.Thread(target = Detection.task2())

    thread1.start()
    thread2.start()    

    thread1.join()    
    thread2.join()