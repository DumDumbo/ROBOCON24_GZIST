#!/usr/bin/env python  
#coding=utf-8


import rospy
from sensor_msgs.msg import LaserScan
import tf2_ros
import tf2_geometry_msgs
import math
import numpy as np

class LaserTransform:
    def __init__(self):

        self.tf_buffer = tf2_ros.Buffer()
        self.tf_listener = tf2_ros.TransformListener(self.tf_buffer)

        self.scan_pub = rospy.Publisher("transformed_scan", LaserScan, queue_size=10)

        rospy.Subscriber("scan", LaserScan, self.scan_callback)

    def scan_callback(self, scan):
        transformed_scan = LaserScan()
        transformed_scan.header = scan.header
        transformed_scan.angle_min = scan.angle_min
        transformed_scan.angle_max = scan.angle_max
        transformed_scan.angle_increment = scan.angle_increment
        transformed_scan.time_increment = scan.time_increment
        transformed_scan.scan_time = scan.scan_time
        transformed_scan.range_min = scan.range_min
        transformed_scan.range_max = scan.range_max

        angle_distance_array = np.zeros((len(scan.ranges), 2))

        for i, distance in enumerate(scan.ranges):
            # 计算每个点的角度(弧度制)
            angle = scan.angle_min + i * scan.angle_increment

            # 将极坐标转换为点
            laser_point = tf2_geometry_msgs.PointStamped()
            laser_point.header.frame_id = scan.header.frame_id
            laser_point.header.stamp = scan.header.stamp
            laser_point.point.x = distance * math.cos(angle)    # 弧度制
            laser_point.point.y = distance * math.sin(angle)     # 弧度制
            laser_point.point.z = 0.0

            try:
                # 转换点到 base_link 坐标系
                base_point = self.tf_buffer.transform(laser_point, 'base_link', rospy.Duration(1.0))
                base_distance = math.sqrt(base_point.point.x**2 + base_point.point.y**2)

                transformed_scan.ranges.append(base_distance)
            except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException) as ex:
                rospy.logwarn("Transform failed: %s", ex)

        # 发布转换后的激光扫描数据
        self.scan_pub.publish(transformed_scan)


if __name__ == '__main__':
    # 初始化节点
    rospy.init_node('laser_point2_base_link', anonymous=True)
    # 实例化
    transform = LaserTransform()
    try:
        rospy.spin()
    except rospy.ROSInterruptException:
        rospy.logwarn("Something went wrong! From laser_point2base_link.py line 64")
