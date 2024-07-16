#!/usr/bin/env python
#coding=utf-8

import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import os
import numpy as np

# 初始化ROS节点
rospy.init_node('sub_image_and_save_it_into_floder', anonymous=True)

# 创建CvBridge实例
bridge = CvBridge()

# 存储图像的文件夹路径
data_folder = "/home/dragon/Desktop/data"

# 计数器
image_count = 0

# 是否保存图像的标志
save_image_flag = False

# 回调函数，处理接收到的图像消息
def image_callback(msg):
    global image_count
    global save_image_flag

    try:
        # 将ROS图像消息转换为OpenCV图像
        cv_image = bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")

        # 在图像上添加文字
        # cv_image_with_text = cv2ImgAddText(cv_image, "ROS Image", 10, 30, (0, 255, 0))
        cv2.imshow("Image", cv_image)
        cv2.waitKey(1)

        if save_image_flag:
            # 保存图像
            img_name = "img_" + str(image_count) + ".jpg"
            img_path = os.path.join(data_folder, img_name)
            cv2.imwrite(img_path, cv_image)

            rospy.loginfo("Saved image to: %s", img_path)

            # 递增计数器
            image_count += 1

            # 保存完后重置保存标志
            save_image_flag = False
    except Exception as e:
        rospy.logerr("Error converting image: %s", str(e))

# 添加文字到图片的函数
def cv2ImgAddText(img, text, left, top, textColor=(0, 255, 0), textSize=20):
    font = cv2.FONT_HERSHEY_SIMPLEX
    cv2.putText(img, text, (left, top), font, textSize, textColor, 2)
    return img

# 键盘输入回调函数
def keyboard_callback(event):
    global save_image_flag

    if raw_input("Press 's' to save image: ").strip().lower() == 's':
        save_image_flag = True
        rospy.loginfo("Saving image...")

# 订阅深度相机话题，这里假设话题名为 "/camera/color/image_raw"
image_subscriber = rospy.Subscriber("/camera/color/image_raw", Image, image_callback)

# 设置键盘输入监听
rospy.Timer(rospy.Duration(0.1), lambda event: keyboard_callback(event), oneshot=False)

rospy.loginfo("Image Saver Node Started")
rospy.spin()