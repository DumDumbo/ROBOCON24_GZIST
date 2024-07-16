#!/usr/bin/env python  
#coding=utf-8

"""
/****************************************************************************************
 * @brief:  本文件为ROS图像消息转换成Opencv图像并依据该图像进行颜色阈值选择例程
 * 
 * @version: 1.0
 * 
 * @author: YYY
 *                     
 * @details: 本例程采用直接在 imageFromRosCallback(msg) 函数中,通过Opencv图像显示函数来
                        判断图像是否转换成功,在实际工程中,不建议直接采用Opencv图像显示函数,因其会导致
                        程序阻塞
 *
#  * @note:   使用本节点时,请先开启Astra S深度相机,因其需要获取深度相机数据话题。
****************************************************************************************/
"""

import cv2
import rospy
from std_msgs.msg import String
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image
import numpy as np


redL = np.array([0,134,45])
redU = np.array([6,255,255])


"""
/*******
 * @brief:	全局定义
 *
*********/
"""
hsv_low = np.array([0, 0, 0])
hsv_high = np.array([0, 0, 0])
def h_low(value):
    hsv_low[0] = value


def h_high(value):
    hsv_high[0] = value


def s_low(value):
    hsv_low[1] = value


def s_high(value):
    hsv_high[1] = value


def v_low(value):
    hsv_low[2] = value


def v_high(value):
    hsv_high[2] = value
cv2.namedWindow('image', cv2.WINDOW_NORMAL | cv2.WINDOW_FREERATIO)
# H low：
#    0：指向整数变量的可选指针，该变量的值反映滑块的初始位置。
#  179：表示滑块可以达到的最大位置的值为179，最小位置始终为0。
# h_low：指向每次滑块更改位置时要调用的函数的指针，指针指向h_low元组，有默认值0。

cv2.createTrackbar('H low', 'image', 0, 179, h_low)
cv2.createTrackbar('H high', 'image', 0, 179, h_high)
cv2.createTrackbar('S low', 'image', 0, 255, s_low)
cv2.createTrackbar('S high', 'image', 0, 255, s_high)
cv2.createTrackbar('V low', 'image', 0, 255, v_low)
cv2.createTrackbar('V high', 'image', 0, 255, v_high)


"""
/*******
 * @brief:	实例化对象
 * 			Instantiate Objects
*********/
"""
# 实例化cvbridge
bridge = CvBridge()


"""*****************************************************
*@FunctionName: rgb2Hsv(img):
*@Parameter:    img
*@Description:  将RGB图像转换为HSV图像格式
*@ReturnVal:    HSV图像格式
*****************************************************"""
def rgb2Hsv(img):
    imgGB = cv2.GaussianBlur(img, (3,3),0)
    hsv_img = cv2.cvtColor(imgGB, cv2.COLOR_BGR2HSV)
    erode_hsv = cv2.erode(hsv_img, None, iterations=2)
    dilated_hsv= cv2.dilate(erode_hsv, None, iterations=2)
    return dilated_hsv


"""*****************************************************
*@FunctionName: imageFromRosCallback():
*@Parameter:    None
*@Description:  Astra S 图像话题回调函数
*@ReturnVal:    None
*****************************************************"""
def imageFromRosCallback(msg):
    cv_image = bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
    hsvImg = rgb2Hsv(cv_image)
    dst = cv2.inRange( hsvImg, hsv_low, hsv_high)  # 通过HSV的高低阈值，提取图像部分区域
    cv2.resize(dst, (640, 480))
    cv2.imshow('dst', dst)
    cv2.waitKey(1)
    
"""*****************************************************
*@FunctionName: ros_main():
*@Parameter:    None
*@Description:  对节点进行ros初始化
*@ReturnVal:    None
*****************************************************"""
def ros_main():
    # 初始化节点
    rospy.init_node("image_hsv_selection_demo")
    # 定义sub对象
    sub = rospy.Subscriber("/camera_astras/color/image_raw", Image,imageFromRosCallback,queue_size=10)
    # sub = rospy.Subscriber("/OpencvImage", Image,imageFromRosCallback,queue_size=10)
    # 循环监听ROS消息
    rospy.spin()





if __name__=="__main__":
    ros_main()
