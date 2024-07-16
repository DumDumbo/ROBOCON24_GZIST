#!/usr/bin/env python
#coding=utf-8

import rospy
from astra_camera.srv import SetInt32
from std_srvs.srv import SetBool
from sensor_msgs.msg import Image

first_image_received = False  # Flag to track the first image received

def set_camera_parameters():
    global first_image_received

    if not first_image_received:
        # Assuming your camera services are named appropriately
        service_auto_white_balance = 'camera_astras/set_auto_white_balance'
        service_auto_exposure = 'camera_astras/set_color_auto_exposure'

        # Call services to set parameters
        try:
            rospy.wait_for_service(service_auto_white_balance)
            set_white_balance = rospy.ServiceProxy(service_auto_white_balance, SetInt32)
            response = set_white_balance(0)  # Assuming 0 means disable auto white balance

            rospy.wait_for_service(service_auto_exposure)
            set_auto_exposure = rospy.ServiceProxy(service_auto_exposure, SetBool)
            response = set_auto_exposure(False)  # Assuming 0 means disable auto exposure

            first_image_received = True  # Set flag to True after first setting
            print "36"
        except rospy.ServiceException as e:
            rospy.logerr("error")

def camera_callback(msg):
    # This function is called whenever a message is received on '/camera_astras/color/image_raw'
    set_camera_parameters()

def listener():
    rospy.init_node('camera_param_setter', anonymous=True)
    rospy.Subscriber('/camera_astras/color/image_raw', Image, camera_callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
