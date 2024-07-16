#!/usr/bin/env python  
#coding=utf-8

"""
/****************************************************************************************
 * @brief:  本文件为Opencv图像转换成ROS图像消息例程
 * 
 * @version: 1.0
 * 
 * @author: YYY
 *                     
 * @details: 
 *
 * @note:   该节点运行后,可使用命令"rosrun rqt_image_view rqt_image_view",
            并选择"opencvImage"话题查看图像 
****************************************************************************************/
"""

import cv2
import rospy
from std_msgs.msg import String
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image

"""
/*******
 * @brief:	实例化对象
 * 			Instantiate Objects
*********/
"""
# 实例化cvbridge
bridge = CvBridge()
# 摄像头选取
cap = cv2.VideoCapture(0)


"""*****************************************************
*@FunctionName: get_Image():
*@Parameter:    None
*@Description:  获取RGB图像
*@ReturnVal:    None
*****************************************************"""
def get_Image():
    # 读取图像
    ret, image = cap.read()
    try:
        if ret:
            return image
        else:
            raise ValueError("图像获取失败，请检测图像输入")

    except ValueError as error:
        print "图像源输入错误:{}".format(error)
        return None  # 返回None表示图像获取失败
    

"""*****************************************************
*@FunctionName: ImageTransformAndPub():
*@Parameter:    None
*@Description:  通过CvBridge将Opencv图像转换成ROS图像消息
*@ReturnVal:    None
*****************************************************"""
def ImageTransformAndPub():
        CvImage = get_Image()
        if CvImage is not None:
            try:
                # 将图像转换为ROS图像消息
                image_message = bridge.cv2_to_imgmsg(CvImage, encoding="bgr8")
                # 发布图像消息到指定话题
                pub.publish(image_message)

            except CvBridgeError as e:
                print "e"


if __name__=="__main__":
    # 初始化节点
    rospy.init_node("image_opencv2ros_pub_demo")
    # 定义puh对象
    pub = rospy.Publisher("OpencvImage",Image,queue_size=10)
    while not rospy.is_shutdown():
        ImageTransformAndPub()
