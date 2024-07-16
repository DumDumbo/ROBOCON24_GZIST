#!/usr/bin/env python  
#coding=utf-8

"""
/****************************************************************************************
 * @brief:  本文件为ROS图像消息转换成Opencv图像例程
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


color = {
    'red' :{'Lower': np.array([0,134,45]), 'Upper': np.array([6,255,255])},
}


redL = np.array([0,134,45])
redU = np.array([6,255,255])
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
    kernel = np.ones((3,3),np.uint8)
    # 图像开运算，去除噪点
    image_openning = cv2.morphologyEx(hsv_img, cv2.MORPH_OPEN, kernel)
    return image_openning


"""*****************************************************
*@FunctionName: 
*@Parameter:   
*@Description: 
*@ReturnVal:   
*****************************************************"""
def binarization(hsvFrame):
    rangeImg = cv2.inRange(hsvFrame,redL,redU)
    kernel= np.ones((3,3),np.uint8)
    # 图像闭运算,去除图形内部黑点
    # image_closing = cv2.morphologyEx(rangeImg, cv2.MORPH_CLOSE, kernel)
    dilated_hsv= cv2.dilate( rangeImg, None, iterations=1)
    erode_hsv = cv2.erode(dilated_hsv, None, iterations=3)
    
    return  erode_hsv 


"""*****************************************************
*@FunctionName: imageFromRosCallback():
*@Parameter:    None
*@Description:  Astra S 图像话题回调函数
*@ReturnVal:    None
*****************************************************"""
def imageFromRosCallback(msg):
    cv_image = bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
    hsvImg = rgb2Hsv(cv_image)
    endImg = binarization(hsvImg)
    cv2.imshow("cv_image", cv_image)
    cv2.imshow("endImg", endImg)
    cv2.waitKey(1)
    
"""*****************************************************
*@FunctionName: ros_main():
*@Parameter:    None
*@Description:  对节点进行ros初始化
*@ReturnVal:    None
*****************************************************"""
def ros_main():
    # 初始化节点
    rospy.init_node("image_ros2opencv_demo")
    # 定义sub对象
    sub = rospy.Subscriber("/camera/rgb/image_rect_color", Image,imageFromRosCallback,queue_size=10)
    # 循环监听ROS消息
    rospy.spin()





if __name__=="__main__":
    ros_main()





