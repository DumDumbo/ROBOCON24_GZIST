#ifndef __ROS_STM32_SERIAL_DEMO_H_
#define __ROS_STM32_SERIAL_DEMO_H_

/*******
 * @brief:	头文件
 * 			Header file
*********/
#include "ros/ros.h"
#include <iostream>
#include <string.h>
#include <string> 
#include <iostream>
#include <math.h>
#include <stdlib.h>    
#include <unistd.h>      
#include <sys/types.h>
#include <sys/stat.h>
#include <serial/serial.h>
#include <fcntl.h>          
#include <stdbool.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Vector3.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>
#include "ros_stm32_serial/serial_topic_msgs.h"
#include <robot_control/machine_status.h>
#include <thread>
using namespace std;

/*******
 * @brief:	宏定义
 * 			Macro definition
*********/
#define SEND_DATA_CHECK   1          //Send data check flag bits //发送数据校验标志位
#define READ_DATA_CHECK   0          //Receive data to check flag bits //接收数据校验标志位
#define FRAME_HEADER      0X7B       //Frame head //帧头
#define FRAME_TAIL        0X7D       		//Frame tail //帧尾
#define RECEIVE_DATA_SIZE 19         //The length of the data sent by the lower computer //下位机发送过来的数据的长度
#define SEND_DATA_SIZE    15        	 //The length of data sent by ROS to the lower machine //ROS向下位机发送的数据的长度
#define PI 				  3.1415926f 				//PI //圆周率


/*******
 * @brief:	机器人小车速度数据结构体
 * 			Data structure for speed and position
*********/
typedef struct __Vel_Data_
{
	float X;
	float Y;
	float Z;
}Vel_Data;



/*******
 * @brief:	机器人激光测距数据结构体
 * 			Data structure for Laser ranging data
*********/
typedef struct __LASER_DATA_
{
	// 机器人前，左，右，后部激光测距数据（ROS右手坐标系）
	unsigned short LaserFront;
	unsigned short LaserL;	
	unsigned short LaserR;
	unsigned short LaserRear;
}LASER_DATA;



/*******
 * @brief:	机器人机构状态结构体
 * 			
*********/
typedef struct __MACHINE_STATUS__
{
    unsigned char Roller;
    unsigned char Mode;
    unsigned char KeepOrNot;
    unsigned char PlaceOrNot;
	string RobotStatus;
}MACHINE_STATUS;



/*******
 * @brief:	ROS向Stm32发送数据的结构体
 * 			The structure of the ROS to send data to the down machine
*********/
typedef struct _SEND_DATA_  
{
	unsigned char tx[SEND_DATA_SIZE];	//接收缓存数组
	struct _Control_Str_
	{
		unsigned char Frame_Header;		//帧头		//1字节
		unsigned char Flag;				//预留标志位	//1字节
		unsigned char Status;		 //预留位	//1字节
		short X_speed;	       			//小车X轴线速度（ROS坐标系）	//2字节
		short Y_speed;           		//小车Y轴线速度（ROS坐标系）	//2字节
		short Z_speed;         			//小车Z轴角速度（ROS坐标系）	//2字节
		unsigned char Roller;	 //控制滚筒是否启动							    //1字节
		unsigned char Mode;		//小球入仓模式变量							   //1字节
		unsigned char KeepOrNot;  		//决策小球是否选择持有		//1字节
		unsigned char PlaceOrNot;  		//决策小球是否释放归仓		 //1字节
		unsigned char Frame_Tail;		//帧尾		//1字节
	}Control_Str;
}SEND_DATA;


/*******
 * @brief:	ROS从Stm32接收数据的结构体
 * 			The structure of ROS receiving data from Stm32
*********/
typedef struct _RECEIVE_DATA_     
{
	unsigned char rx[RECEIVE_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned char Frame_Header;		//帧头		//1字节
		unsigned char Flag;							//机器人是否重置标志位	//1字节
		unsigned char Status;					 //预留位	//1字节
		short X_speed;	       							//小车X轴线速度（ROS坐标系）	//2字节
		short Y_speed;           						//小车Y轴线速度（ROS坐标系）	//2字节
		short Z_speed;         							//小车Z轴角速度（ROS坐标系）   //2字节
		unsigned short LaserFront;			//前部激光测距数据							 // 2字节
		unsigned short LaserL;					//左侧激光测距数据						  	  //2字节
		unsigned short LaserR;					//右侧激光测距数据						  	  //2字节
		unsigned short LaserRear;			//后部激光测距数据						  	  //2字节
		unsigned char Frame_Tail;			//帧尾		//1字节
	}Sensor_Str;
}RECEIVE_DATA;


/*******
 * @brief:	机器人底盘类，使用构造函数初始化数据和发布话题等
 * 			The robot chassis class uses constructors to initialize data, publish topics, etc
*********/
class robot
{
	public:
		robot();  			//Constructor //构造函数 //初始化相关参数
		serial::Serial Stm32_Serial; 	//Declare a serial object //声明串口对象 
		void serial_ros2stm32();		//Sending data //ROS向Stm32发送数据函数
		void serial_data_pub();			//Receiving data and pub //将接收到的数据按要求发布话题
	private:
		ros::NodeHandle n; //Create a ROS node handle //创建ROS节点句柄
		
		//初始化话题订阅者
		ros::Subscriber Cmd_Vel_Sub;  
		ros::Subscriber Machine_Status_Sub;

		//初始化话题发布者
		ros::Publisher serial_data_publisher;  

		void pub_serial_data();//串口数据发布函数

		bool serial_data_from_stm32();	//Receiving data //ROS从Stm32接收数据函数
		void Cmd_Vel_Callback(const geometry_msgs::Twist &twist_aux);	//速度话题订阅回调函数
		void MachineStatusCallback(const robot_control::machine_status &msg); //机器状态话题订阅回调函数

		
		float Odom_Trans(uint8_t Data_High,uint8_t Data_Low);//接收速度数据转化函数
		unsigned short Laser_Trans(uint8_t Data_High,uint8_t Data_Low);//激光测距数据转化函数
		
        unsigned char Check_Sum(unsigned char Count_Number,unsigned char mode); //BBC check function //BBC校验函数 

		//Define the related variables //定义相关变量
        string usart_port_name;		//变量//串口名称
        int serial_baud_rate;     	//变量///串口通信波特率
	 	short  linearX, linearY, angularZ;  //速度变量

		ros::Time time1;
		double time;

		//实例化对象
        RECEIVE_DATA Receive_Data; //串口接收数据结构体
        SEND_DATA Send_Data;       		//串口发送数据结构体
        Vel_Data Robot_Vel;        			  //机器人小车速度
		LASER_DATA Laser_Data; 		   //激光测距数据 
		MACHINE_STATUS machine_status; 	//机械状态结构体
};
#endif
