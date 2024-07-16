#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <iostream>
#include <cmath>



// void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
// {
//     // double distance = msg->pose.pose.position.x;
//     // double targetPoint = 1.000;
//     // double diff = targetPoint-distance;
//     // geometry_msgs::Twist vel_msg;
//     // vel_msg.linear.x =diff* 1.3;

//     // if(distance >=1.0 && distance< 1.003) 
//     // {
//     //     vel_msg.linear.x = 0.0;
//     // }
    
//     // if( vel_msg.linear.x > 1){vel_msg.linear.x =0.5;}

//     geometry_msgs::Twist vel_msg;
//     vel_msg.linear.y =0.4;
//     vel_msg.angular.z = 0.4;
//     vel_pub.publish(vel_msg);
// }



int main(int argc, char *argv[])
{
    ros::init(argc, argv, "vel_node");

    ros::NodeHandle ad;
    // ros::Subscriber odom_sub = ad.subscribe("odom", 1, &odomCallback);
     ros::Publisher vel_pub = ad.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    geometry_msgs::Twist vel_msg;
    vel_msg.linear.x = 0.0;
    vel_msg.linear.y = 0.4;
    vel_msg.angular.z = 0.0;


    while(ros::ok())
    {
        vel_pub.publish(vel_msg);
        // ros::spinOnce();
    }

    return 0;
}


