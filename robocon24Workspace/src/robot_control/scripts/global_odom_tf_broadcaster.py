#!/usr/bin/env python  
#coding=utf-8

"""
/****************************************************************************************
 * @brief:  实时发布Odom_combined 与 map之间的tf变换关系
 * 
 * @version: 
 * 
 * @author: YYY
 *                     
 * @details: 

  * @note:   
****************************************************************************************/
"""

import  rospy
import tf
from geometry_msgs.msg import TransformStamped, PointStamped
from nav_msgs.msg import Odometry


class transform:
    def __init__(self):
        rospy.init_node("global_odom_tf_broadcaster")
        # 创建TransformBroadcaster对象
        self.tf_broadcaster = tf.TransformBroadcaster()    
        # 订阅 odom_combined 话题
        self.odom_sub = rospy.Subscriber("odom_combined", Odometry, self.odomCallback)
        # 初始化存储里程计数据变量
        self.odom_data = None

    def odomCallback(self, msg):
        self.odom_data = msg
        self.broadcast_transform()

    def broadcast_transform(self):
        #创建TransformStamped消息
        transform_stamped = TransformStamped()
        transform_stamped.header.stamp = rospy.Time.now()
        transform_stamped.header.frame_id = "global"
        transform_stamped.child_frame_id = "odom_combined"
        # 数据赋值
        translation = (self.odom_data.pose.pose.position.x,
                                    self.odom_data.pose.pose.position.y,
                                    self.odom_data.pose.pose.position.z)
        rotation = (self.odom_data.pose.pose.orientation.x,
                                self.odom_data.pose.pose.orientation.y,
                                self.odom_data.pose.pose.orientation.z,
                                self.odom_data.pose.pose.orientation.w)
        # 发布变换
        self.tf_broadcaster.sendTransform(transform_stamped)


if __name__=="__main__":
    try:
        while not rospy.is_shutdown():
            Publisher = transform()
            rospy.spin()
    except rospy.ROSInterruptException:
        pass
