#ifndef __ROBOT_CONTROL_DEMO_H_
#define __ROBOT_CONTROL_DEMO_H_

/*******
 * @brief:	头文件
 * 			Header file
*********/
//C++
#include <string.h>
#include <stdlib.h>   
#include <iostream>
#include <cmath>
#include <thread>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <map>
//ROS
#include "ros/ros.h"
#include <sensor_msgs/Imu.h>
#include "target_detection/Locked.h"
#include "target_detection/msgLocked.h"
#include <std_msgs/Header.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Quaternion.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/time_synchronizer.h>
#include <tf/tf.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <robot_control/msg4pid.h>
#include <robot_control/machine_status.h>
#include "ros_stm32_serial/serial_topic_msgs.h"
#include "yolov5_ros_msgs/BoundingBox.h"
#include "yolov5_ros_msgs/BoundingBoxes.h"

using namespace std;


/*******
 * @brief:	IMU数据结构体
 * 			
*********/
typedef struct __IMU_DATA_
{
    // 四元数
    struct __Quaternion__
    {
        float x; 
        float y;
        float z;
        float w;
    }Quaternion;

    // 欧拉角Euler angles
    struct __Euler__
    {
        float roll;
        float pitch;
        float yaw;
    }Euler;

    // 三轴角速度rad/s
    struct __AngularVelocity__
    {
        float angularVelocity_X; 
	    float angularVelocity_Y; 	
	    float angularVelocity_Z; 
    }AngularVelocity;

    //三轴线性加速度m/s^2
    struct __LinearAcceleration__
    {
        float acceleration_X;         
	    float acceleration_Y; 	
	    float acceleration_Z; 
    }LinearAcceleration;
    
}IMU_DATA;



/*******
 * @brief:	激光测距模块数据结构体（数据来自下位机）
 * 			
*********/
typedef struct __LASER_RANGING_
{
    //机器人前、左、右、后部 激光测距模块
    float LaserFront;   
    float LaserL;       
    float LaserR; 
    float LaserRear;
}LASER_RANGING;



/*******
 * @brief:	谷仓状态结构体
 * 			
*********/
typedef struct __BARN_STATUS__
{
    std::vector<std::string> barns; 
}BARN_STATUS;



/*******
 * @brief:	谷仓位置结构体
 * 			
*********/
typedef struct __BARN_POSITION_INDEX__
{
    float sideFace;
    float Rear;
}BARN_POSITION_INDEX;



/*******
 * @brief:	机器人机构状态结构体
 * 			
*********/
typedef struct __MACHINE_STATUS__
{
    int8_t Roller;
    int8_t Mode;
    int8_t KeepOrNot;
    int8_t PlaceOrNot;
}MACHINE_STATUS;



/*******
 * @brief:	目标位置数据结构体(标签名、三维坐标、角度，目标框像素坐标点)
 * 			
*********/
typedef struct __TARGET_POS__
{
    string Class;           
    float x3;
    float y3;
    float z3;
    float angleX;           //依据视场角计算而得，也可对上述三维坐标进行三角转换获得
    float angleY;
    uint16_t centerX;
    uint16_t centerY;
}TARGET_POS;



/*******
 * @brief:	机器人位置数据结构体(三维坐标)
 * 			
*********/
typedef struct __ROBOT_POS__
{
    float posX;
    float posY;
    float posZ;
}ROBOT_POS;



/*******
 * @brief:	PID控制器
 * 			
*********/
class PIDController{
    private:
        ros::Publisher pidDataPub;
        ros::NodeHandle nh;

        // x轴pid
        double kp_x;                          //比例增益
        double ki_x;                          //积分增益
        double kd_x;                          //微分增益
        double integral_x;                    //积分项
        double prev_error_x;                  //上一次误差
        ros::Time _Now_x, _Last_Time_x; 
        double dt_x;                          //积分时间
        double derivative_x;                  //微分项
        double output_x;                      //输出

        //  y轴pid
        double kp_y;                          //比例增益
        double ki_y;                          //积分增益
        double kd_y;                          //微分增益
        double integral_y;                    //积分项
        double prev_error_y;                  //上一次误差
        ros::Time _Now_y, _Last_Time_y; 
        double dt_y;                          //积分时间
        double derivative_y;                  //微分项
        double output_y;                      //输出

        //  Z轴pid
        double kp_z;                          //比例增益
        double ki_z;                          //积分增益
        double kd_z;                          //微分增益
        double integral_z;                    //积分项
        double prev_error_z;                  //上一次误差
        ros::Time _Now_z, _Last_Time_z; 
        double dt_z;                          //积分时间
        double derivative_z;                  //微分项
        double output_z;                      //输出

        //  Yaw Pid
        double kp_yaw;                          //比例增益
        double ki_yaw;                          //积分增益
        double kd_yaw;                          //微分增益
        double integral_yaw;                    //积分项
        double prev_error_yaw;                  //上一次误差
        ros::Time _Now_yaw, _Last_Time_yaw; 
        double dt_yaw;                          //积分时间
        double derivative_yaw;                  //微分项
        double output_yaw;                      //输出


        
    public:
        PIDController();            // 构造函数

        //位置式pid计算函数
        double computeCommandLocationForX(double setpoint, double feedback);   // x_Axis
        double computeCommandLocationForY(double setpoint, double feedback);   // y_Axis
        double computeCommandLocationForZ(double setpoint, double feedback);   //z_Axis
        double computeCommandLocationForYaw(double setpoint, double feedback);   //Yaw
        

        // pid参数发布函数（用于pid调参可视化）
        void pidParameterPub(double kp, double ki, double kd,double  setpoint, double feedback);
};






class RcController{
    private:

        ros::NodeHandle n;         //创建ROS节点句柄
       
        ros::Publisher cmd_vel_pub; //发布者
        ros::Publisher machine_contorl_pub;

        // 话题回调函数
        void imuCallback(const sensor_msgs::Imu::ConstPtr& imu_msg);
        void lockedCallback(const target_detection::Locked::ConstPtr& locked_msg);
        // void robotOdomCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& robotOdom_msg);
        void barnCallback(const yolov5_ros_msgs::BoundingBoxes::ConstPtr& barn_msg);
        void serialMsgCallback(const ros_stm32_serial::serial_topic_msgs& serial_msg);
        void ballColorCallback(const std_msgs::String& ballColormsg);

        // 机器人运动速度获取
        double computeLimitedPIDOutput(char axis, double setpoint, double feedback, double max_speed);
        // 机器人运动速度限制
        double limitSpeed(double speed, double max_speed);
        // 获取本方队伍颜色
        string getAreaColor();
        // 发布机械状态控制话题
        void machineStatusPub();


        /******
        * * @brief:	运动逻辑处理
        **********/
        void handleInitialMovement(float& laserD, ros::Rate& rate);
        void handlePreGrainSearch(float& laserD, ros::Rate& rate);
        void handleSearching(bool& aligned_with_ball, ros::Rate& rate);
        void handlePreHoming(float& laserD, ros::Rate& rate);
        void handleHoming(float& laserD, ros::Rate& rate);
        void handleHomingArrived(float& laserD, ros::Rate& rate);
                                                             
        // 订阅imu话题
        ros::Subscriber imu_Sub;
        ros::Subscriber locked_Sub;
        // ros::Subscriber robotOdom_Sub;
        ros::Subscriber serialMsg_Sub;  //用于获取通讯话题中的激光测距数据
        ros::Subscriber barn_sub;
        ros::Subscriber ballColor_sub;

        // 变量定义
        tf2::Quaternion current_orientation;                // 小车当前姿态（四元数）
        double roll, pitch, yaw;                            // 用于接收解算的四元数
        double PIDOutputX, PIDOutputY, PIDOutputZ, PIDOutputYaw;          // PID速度发布
        bool initial_orientation_set;                       //用于判断是否已经设置机器人初始姿态（欧拉角）
        double initial_roll, initial_pitch, initial_yaw;    //初始滚转角, 俯仰角, 航向角
        double search_yaw; // 搜寻谷粒时的控制航向角（初始状态时与initial_yaw相等）
        string RobotStatus;                                 //机器人状态
        float KeepX;                                        //初始运动的x轴目标值
        float KeepY;                                        //初始运动的y轴目标值
        int barnsIndex;                                     // 谷仓索引
        string areaColor;                                   // 本方队伍颜色
        std::map<int, BARN_POSITION_INDEX> barnMap; //谷仓位置数据
        float barnX;
        float barnY;
        string ballColor;
        bool ResetMachine;
        int flag1;

        ros::Time time1, time2;
        double time;
        ros::Time last_time;        // 用于计算里程积分

        // 实例化消息变量
        target_detection::msgLocked pos;    //用于接收msgLocked话题中的数据
        geometry_msgs::Twist cmd_vel_msg;

        // 实例化结构体
        IMU_DATA Imu_Data;
        TARGET_POS target_pos;
        ROBOT_POS robot_pos;
        LASER_RANGING Laser_Ranging;
        BARN_STATUS barn_status;
        MACHINE_STATUS machine_status;

        // 实例化pid类
        PIDController PID;

    public:
        RcController();         //构造函数
        void CallbackThread();  //回调函数运行线程
        void UnifiedControl(); // 运动控制函数

};


#endif
