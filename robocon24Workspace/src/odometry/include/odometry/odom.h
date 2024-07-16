#ifndef __ODOM_H_
#define __ODOM_H_

/*******
 * @brief:	头文件
 * 			Header file
*********/ 
//C++
#include <math.h>
// Ros
#include "ros/ros.h"
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <ros_stm32_serial/serial_topic_msgs.h>
#include <std_msgs/Header.h>
#include <tf/tf.h>

using namespace std;


/*******
 * @brief:	协方差矩阵，用于里程计话题数据，用于robt_pose_ekf功能包
 * 			Covariance matrix for speedometer topic data for robt_pose_ekf feature pack
*********/
const double odom_pose_covariance[36]   = {1e-3,    0,    0,   0,   0,    0, 
										      0, 1e-3,    0,   0,   0,    0,
										      0,    0,  1e6,   0,   0,    0,
										      0,    0,    0, 1e6,   0,    0,
										      0,    0,    0,   0, 1e6,    0,
										      0,    0,    0,   0,   0,  1e6 };

const double odom_pose_covariance2[36]  = {1e-9,    0,    0,   0,   0,    0, 
										      0, 1e-3, 1e-9,   0,   0,    0,
										      0,    0,  1e6,   0,   0,    0,
										      0,    0,    0, 1e6,   0,    0,
										      0,    0,    0,   0, 1e6,    0,
										      0,    0,    0,   0,   0, 1e3 };

const double odom_twist_covariance[36]  = {1e-3,    0,    0,   0,   0,    0, 
										      0, 1e-3,    0,   0,   0,    0,
										      0,    0,  1e6,   0,   0,    0,
										      0,    0,    0, 1e6,   0,    0,
										      0,    0,    0,   0, 1e6,    0,
										      0,    0,    0,   0,   0,  1e6 };
										      
const double odom_twist_covariance2[36] = {1e-9,    0,    0,   0,   0,    0, 
										      0, 1e-3, 1e-9,   0,   0,    0,
										      0,    0,  1e6,   0,   0,    0,
										      0,    0,    0, 1e6,   0,    0,
										      0,    0,    0,   0, 1e6,    0,
										      0,    0,    0,   0,   0, 1e3} ;



/*******
 * @brief:	小车位置数据结构体
 * 			The structure of the Car's position
*********/
typedef struct __CAR_POS_DATA_
{
    float X;
    float Y;
    float Z;
}CAR_POS_DATA;

/*******
 * @brief:	串口通信数据结构体
 * 			The structure of the Serial data
*********/
typedef struct __SERIAL_DATA__
{
    float flag;
    float status;
    float linearX;
    float linearY;
    float angularZ;
}SERIAL_DATA;


class CarOdom
{
    private:
        ros::NodeHandle n;
        ros::Subscriber vel_sub;
        ros::Subscriber serialDataSub;

        ros::Publisher Odom_Pub;

        // 积分相关
        ros::Time _Now, _Last_Time;
        float Sampling_Time;

        // 串口数据回调函数
        void serialDataCallback(const ros_stm32_serial::serial_topic_msgs::ConstPtr& msg);
        // 轮式里程计发布函数
        void Publish_Odom();
        
        //实例化结构体
        SERIAL_DATA SerialData;     
        CAR_POS_DATA CarPos;
        


    public:
        CarOdom();          //构造函数

};


#endif

