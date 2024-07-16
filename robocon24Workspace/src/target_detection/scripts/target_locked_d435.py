#!/usr/bin/env python
#coding=utf-8

"""
/****************************************************************************************
 * @brief:  从目标话题中获取离机器人最近的小球，并计算其三维坐标发布至/Locked话题
 * 
 * @version: 1.0
 * 
 * @author: YYY
 *                     
 * @details: 	  订阅话题:		/posTargets
 *			                发布话题:     /Locked
 *				            相机型号： Intel D435
 *
 * @note:   
****************************************************************************************/"""

import rospy
import numpy as np
from target_detection.msg import position, Positions, msgLocked, Locked
import tf2_ros
import tf2_geometry_msgs
from geometry_msgs.msg import PointStamped
from tf import transformations as tf_trans
from std_msgs.msg import Header
import math


from visualization_msgs.msg import Marker


class TargetLocked:

        def __init__(self):
                
                self.tragetPos_sub = rospy.Subscriber("/posTargets", Positions, self.lockedCallback,queue_size=1)
                
                self.cameraMatrix =np.array([[607.1786499023438, 0.0, 321.0275573730469],
                                                                        [0.0, 605.9725341796875, 243.97653198242188],
                                                                        [ 0.0, 0.0, 1.0]], dtype=np.float32)
                                                                        
		self.lockedPublisher = rospy.Publisher('/Locked', Locked, queue_size=1)
                self.markerPublisher = rospy.Publisher('/visualization_marker', Marker, queue_size=1)
                self.posBaseLink = None
                self.nearestTarget = None

                # 实例化Buffer以及Listener
                self.tf_buffer = tf2_ros.Buffer()
                self.tf_listener = tf2_ros.TransformListener(self.tf_buffer)

                self.header = Header()

        def pixel_coord_to_camera_coord(self, pixel_x, pixel_y, depth, fx, fy, cx, cy):
                # 得到的是物體在相機坐標系下的真實距離值
                x_c = (pixel_x - cx)*depth / fx
                y_c = (pixel_y - cy)*depth / fy
                z_c = depth
                return x_c, y_c, z_c
                
        def posTransform2Base_link(self, x, y, z, frame_id):
                # print frame_id
                posCamera = PointStamped()
                posCamera.header.stamp = rospy.Time.now()
                posCamera.header.frame_id = frame_id
                posCamera.point.x = x/1000
                posCamera.point.y = y/1000
                posCamera.point.z = z/1000     #tf坐标的平移关系单位是m，但是上述内参需要的深度距离是mm，故这里需要转换成m供坐标变换使用
                
                try:
                        # 等待变换关系可用
                        transform = self.tf_buffer.lookup_transform('base_link', frame_id, rospy.Time(0), rospy.Duration(1.0))
                        # 将物体姿态转换到Base_link坐标系下
                        self.posBaseLink = tf2_geometry_msgs.do_transform_point(posCamera, transform)

                        # # 计算物体与base_link的角度偏角(弧度制)
                        # angle = math.atan2(self.posBaseLink.point.y,  self.posBaseLink.point.x)
                        # rospy.loginfo("posBaseLink: x=%f, y=%f, z=%f, a=%f",  self.posBaseLink.point.x,  self.posBaseLink.point.y,  self.posBaseLink.point.z, angle)
                
                except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException):
                        rospy.logwarn("Failed to transform target position to base_link frame, From target_locked.py line 64.")


        def lockedMsgAppend(self):
                msg = msgLocked()
                msg.Class =  self.nearestTarget.Class
                if(msg.Class == "BlueBall" or msg.Class == "RedBall"):
                        msg.centerX =  self.nearestTarget.centerX
                        msg.centerY = self.nearestTarget.centerY
                        msg.centerX_3 = round(self.posBaseLink.point.x, 3)       #将单位m，精度mm，同下
                        msg.centerY_3 = round(self.posBaseLink.point.y, 3)
                        msg.centerZ_3 = round(self.posBaseLink.point.z, 3)
                        msg.angleX =  self.nearestTarget.angleX* 180.0 / math.pi
                        msg.angleY =  self.nearestTarget.angleY* 180.0 / math.pi
                else:
                        msg.centerX = self.nearestTarget.centerX
                        msg.centerY = self.nearestTarget.centerY
                        msg.centerX_3 = 0.0     #将单位m，同下
                        msg.centerY_3 = 0.0
                        msg.centerZ_3 = 0.0
                        msg.angleX =  0.0
                        msg.angleY =  0.0

                self.lockedMsg.pos.append(msg)
                # 在rviz中可视化小球
                # self.publish_marker(msg.centerX_3, msg.centerY_3, msg.centerZ_3)

        # 在rviz中可视化小球
        def publish_marker(self, X_3, Y_3, Z_3):
                marker = Marker()
                marker.header.frame_id = "base_link"
                marker.header.stamp = rospy.Time.now()
                marker.ns = "target"
                marker.id = 0
                marker.type = Marker.SPHERE
                marker.action = Marker.ADD
                marker.pose.position.x = X_3
                marker.pose.position.y = Y_3
                marker.pose.position.z = Z_3
                marker.pose.orientation.x = 0.0
                marker.pose.orientation.y = 0.0
                marker.pose.orientation.z = 0.0
                marker.pose.orientation.w = 1.0
                marker.scale.x = 0.05
                marker.scale.y = 0.05
                marker.scale.z = 0.05
                marker.color.r = 1.0
                marker.color.g = 0.0
                marker.color.b = 0.0
                marker.color.a = 1.0
                self.markerPublisher.publish(marker)



        def lockedCallback(self, targets_data):
                self.lockedMsg = Locked()
                self.lockedMsg.header =  self.header
                self.lockedMsg.header.stamp = rospy.Time.now()
                self.lockedMsg.header.frame_id = 'base_link'

                #从画面中寻找x轴和y轴最接近320，480的点
                self.nearestTarget = min(targets_data.positions, key=lambda position: abs(position.centerX - 320) + abs(position.centerY-480))

                # 将目标点数据转换到摄像头坐标下
                # print("nearestTarget", self.nearestTarget)
                x, y, z = self.pixel_coord_to_camera_coord(self.nearestTarget.centerX, self.nearestTarget.centerY, self.nearestTarget.distance,
                                                                        self.cameraMatrix[0][0], self.cameraMatrix[1][1], self.cameraMatrix[0][2], self.cameraMatrix[1][2])
                # print ("x", x)
                # print("y", y)
                # print("z", z)
                # 目标点数据转换到Base_link下
                self.posTransform2Base_link(x, y, z, targets_data.header.frame_id)

                # 发布消息
                self.lockedMsgAppend()
                self.lockedPublisher.publish(self.lockedMsg)

                

if __name__ == '__main__':

	# ros节点初始化
	rospy.init_node('target_locked_d435.py')

	# 实例化类
	TLocked = TargetLocked()

	try:
		rospy.spin()
	except rospy.ROSInterruptException:
		rospy.logwarn('failed')


               


