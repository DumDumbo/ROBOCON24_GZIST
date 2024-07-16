#!/usr/bin/env python  
#coding=utf-8


import rospy
import tf
from geometry_msgs.msg import TransformStamped

def publish_transform():
    rate = rospy.Rate(20)
    while not rospy.is_shutdown():
        try:
            # 获取 map 到 base_link 的变换
            (trans, rot) = listener.lookupTransform('/map', '/base_link', rospy.Time(0))
            
            # 创建 TransformStamped 消息
            transform_msg = TransformStamped()
            transform_msg.header.stamp = rospy.Time.now()
            transform_msg.header.frame_id = 'map'
            transform_msg.child_frame_id = 'base_link'
            
            transform_msg.transform.translation.x = trans[0]
            transform_msg.transform.translation.y = trans[1]
            transform_msg.transform.translation.z = trans[2]
            transform_msg.transform.rotation.x = rot[0]
            transform_msg.transform.rotation.y = rot[1]
            transform_msg.transform.rotation.z = rot[2]
            transform_msg.transform.rotation.w = rot[3]
            
            # 发布变换消息
            tf_pub.publish(transform_msg)
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException) as e:
            rospy.logwarn("Failed to get transform: %s", e)
            continue

        rate.sleep()


if __name__ == '__main__':        
    rospy.init_node('listener_for_map2baselink')
    listener = tf.TransformListener()
    tf_pub = rospy.Publisher('/map_to_base_link', TransformStamped, queue_size=3)
    try:
        publish_transform()
    except rospy.ROSInterruptException:
        pass

