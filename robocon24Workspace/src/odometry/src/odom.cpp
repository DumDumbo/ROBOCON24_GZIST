/**
 * @brief:  轮式里程计发布节点
*/

#include "odometry/odom.h"



/******
 * @name:int main(int argc, char** argv)
 * @brief: 主函数
*/
int main(int argc, char** argv)
{
    ros::init(argc, argv, "odom");
    // 实例化对象
    CarOdom ODOM;
  

    while (ros::ok())
    {
        ros::spinOnce();
    }
    return 0;
}



/******
 * @name:CarOdom():serialDataSub(n, "serial_data", 1, &serialDataCallback)
 * @brief: 构造函数
*/
CarOdom::CarOdom()
{
    // 清空结构体数据
    memset(&SerialData, 0, sizeof(SerialData));
    memset(&CarPos, 0, sizeof(CarPos));

    // 话题订阅者
    serialDataSub = n.subscribe("serial_data", 1, &CarOdom::serialDataCallback, this);

    // 话题发布者
    Odom_Pub = n.advertise<nav_msgs::Odometry>("odom", 1);

    _Last_Time = ros::Time::now();

    ROS_INFO_STREAM("\033[1;32mOdom Pub Node Initialized \033[0m");
}



/******
 * @name:CarOdom::serialDataCallback(const ros_stm32_serial::serial_topic_msgs::ConstPtr& msg)
 * @brief: 串口数据回调函数
*/
void CarOdom::serialDataCallback(const ros_stm32_serial::serial_topic_msgs::ConstPtr& msg)
{
    SerialData.flag = msg->flag;
    SerialData.status = msg->status;
    SerialData.linearX = msg->linearX;
    SerialData.linearY = msg->linearY;
    SerialData.angularZ = msg->angularZ;

    // _Last_Time = ros::Time::now(); 
    _Now = ros::Time::now();
    //采样时间
    Sampling_Time = (_Now - _Last_Time).toSec();

    // 积分算里程
    CarPos.X +=(SerialData.linearX * cos(SerialData.angularZ) - SerialData.linearY * sin(SerialData.angularZ)) *  Sampling_Time;
    CarPos.Y +=(SerialData.linearX * sin(SerialData.angularZ) + SerialData.linearY * cos(SerialData.angularZ)) *  Sampling_Time;
    CarPos.Z += SerialData.angularZ * Sampling_Time;
    
    
    // std::cout <<"Sampling_Time:"<< Sampling_Time << std::endl;
    Publish_Odom();

    _Last_Time = _Now; 

}


/******
 * @name:CarOdom::serialDataCallback(const ros_stm32_serial::serial_topic_msgs::ConstPtr& msg)
 * @brief: 串口数据回调函数
*/
void CarOdom::Publish_Odom()
{
    // 把Z轴转角转换为四元数表达
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(SerialData.angularZ);

    // Odom里程计设置
    nav_msgs::Odometry odom;
    odom.header.stamp = ros::Time::now();
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";

    // 设置各个轴的位移量
    odom.pose.pose.position.x = CarPos.X;
    odom.pose.pose.position.y = CarPos.Y;
    odom.pose.pose.position.z = 0;

    // 设置姿态（四元数）
    odom.pose.pose.orientation = odom_quat;

    // 设置各轴线速度
    odom.twist.twist.linear.x = SerialData.linearX;
    odom.twist.twist.linear.y = SerialData.linearY;
    // odom.twist.twist.linear.z = SerialData.linearZ;            //小车忽略z轴速度

    // 设置各轴角速度
    // odom.twist.twist.angular.x = SerialData.angularX;            //忽略
    // odom.twist.twist.angular.y = SerialData.angularY;            //忽略
    odom.twist.twist.angular.z = SerialData.angularZ;

    //这个矩阵有两种，分别在机器人静止和运动的时候使用。扩展卡尔曼滤波官方提供的2个矩阵，用于robot_pose_ekf功能包
    if( SerialData.linearX== 0 &&  SerialData.linearY== 0 && SerialData.angularZ == 0)
    {
        // 如果velocity是零，说明编码器的误差会比较小，认为编码器数据更可靠
        memcpy(&odom.pose.covariance, odom_pose_covariance2, sizeof(odom_pose_covariance2)),
        memcpy(&odom.twist.covariance, odom_twist_covariance2, sizeof(odom_twist_covariance2));
    } 
    else
    {
        //如果小车velocity非零，考虑到运动中编码器可能带来的滑动误差，认为imu的数据更可靠
        memcpy(&odom.pose.covariance, odom_pose_covariance, sizeof(odom_pose_covariance)),
        memcpy(&odom.twist.covariance, odom_twist_covariance, sizeof(odom_twist_covariance));       
    }

    Odom_Pub.publish(odom);
}