/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32_ros_serial.h
  * @brief   This file contains all the function prototypes for
  *          the stm32_ros_serial.c file
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* USER CODE END Header */
#ifndef MESSAGE_TASK_H
#define MESSAGE_TASK_H


/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "gld_can.h"
#include "pid.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"



/* USER CODE BEGIN PV */
extern uint8_t Interrupt_Buffer[1];  //接收中断缓存大小
/* USER CODE END PV */


/* USER CODE BEGIN Private defines */
#define SEND_DATA_CHECK   1        //Send data check flag bits //发送数据校验标志位
#define READ_DATA_CHECK   0        //Receive data to check flag bits //接收数据校验标志位
#define FRAME_HEADER      0X7B 		 //Frame_header //帧头
#define FRAME_TAIL        0X7D 		 //Frame_tail   //帧尾
#define SEND_DATA_SIZE    19	 		 //发送数据的总字节
#define RECEIVE_DATA_SIZE 15	 		 //接收数据的总字节
	

/*******The structure of the serial port sending data************/
/*******串口发送数据的结构体*************************************/
typedef struct _SEND_DATA_  
{
	unsigned char buffer[SEND_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned char Frame_Header; //帧头						//1 bytes
		unsigned char Flag; 				//预留标志位			//1 bytes
		unsigned char Status;				//预留状态位			//1 bytes
		short X_speed;	            //机器人X轴速度 	//2 bytes
		short Y_speed;              //机器人Y轴速度  	//2 bytes
		short Z_speed;              //机器人Z轴速度  	//2 bytes
		unsigned short LaserFront;	//前部激光测距		//2 bytes
		unsigned short LaserL;			//左侧激光测距		//2 bytes
		unsigned short LaserR;			//右侧激光测距		//2 bytes
		unsigned short LaserRear;		//后部激光测距		//2 bytes
		unsigned char Frame_Tail;   //帧尾 						//1 bytes
	}Sensor_Str;
}SEND_DATA;	

/*******The structure of the serial port receiving data************/
/*******串口接收数据的结构体*************************************/
typedef struct _RECEIVE_DATA_  
{
	unsigned char buffer[RECEIVE_DATA_SIZE];
	struct _Control_Str_
	{
		unsigned char Frame_Header; //帧头						//1 bytes
		unsigned char Flag;					//预留标志位			//1 bytes
		unsigned char Status;				//预留状态位			//1 bytes
		short X_speed;	            //机器人X轴速度 	//2 bytes
		short Y_speed;              //机器人Y轴速度  	//2 bytes
		short Z_speed;              //机器人Z轴速度  	//2 bytes
		unsigned char Roller;				//控制滚筒是否启动//1 bytes
		unsigned char Mode;					//小球入仓模式变量//1 bytes
		unsigned char KeepOrNot;		//决策小球是否持有//1 bytes
		unsigned char PlaceOrNot;		//决策小球是否归仓//1 bytes
		unsigned char Frame_Tail;   //帧尾 						//1 bytes
	}Control_Str;
}RECEIVE_DATA;


/*******The structure of the MACHINE_STATUS************/
/*******数据接收的结构体*************************************/
typedef struct _ROBOT_CONTROL_  
{
	unsigned char Frame_Header; //帧头						//1 bytes
	unsigned char Flag;					//预留标志位			//1 bytes
	unsigned char Status;				//预留状态位			//1 bytes
	short X_speed;	            //机器人X轴速度 	//2 bytes
	short Y_speed;              //机器人Y轴速度  	//2 bytes
	short Z_speed;              //机器人Z轴速度  	//2 bytes
	unsigned char Roller;				//控制滚筒是否启动//1 bytes
	unsigned char Mode;					//小球入仓模式变量//1 bytes
	unsigned char KeepOrNot;		//决策小球是否持有//1 bytes
	unsigned char PlaceOrNot;		//决策小球是否归仓//1 bytes
	unsigned char Frame_Tail;   //帧尾 						//1 bytes
}ROBOT_CONTROL;


/*******The structure of the MACHINE_STATUS************/
/*******机械状态的结构体*************************************/
typedef struct _MACHINE_STATUS_  
{
	unsigned char Roller;				//控制滚筒是否启动//1 bytes
	unsigned char Mode;					//小球入仓模式变量//1 bytes
	unsigned char KeepOrNot;		//决策小球是否持有//1 bytes
	unsigned char PlaceOrNot;		//决策小球是否归仓//1 bytes
}MACHINE_STATUS;
/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

/**************************Function declaration******************************/
/*******************************函数声明*************************************/
void message_task(void const * argument);			//FreeRtos函数任务
unsigned char Check_Sum(unsigned char Count_Number,unsigned char Mode);		//声明校验函数

//stm32发送数据至上位机
void data_transition(void);					//数据赋值函数
void stm32_2_ros(void);							//数据向上发送函数

//stm32接收上位机数据
short received_data_trans(uint8_t Data_High, uint8_t Data_Low);		// 数据转换函数
void receive_data_from_ros(void);


extern SEND_DATA Send_Data;
extern RECEIVE_DATA Receive_Data;
extern MACHINE_STATUS Machine_Status;
extern ROBOT_CONTROL Robot_Control;

/* USER CODE END Prototypes */

#endif


