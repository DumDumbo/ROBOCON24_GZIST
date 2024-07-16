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
extern uint8_t Interrupt_Buffer[1];  //�����жϻ����С
/* USER CODE END PV */


/* USER CODE BEGIN Private defines */
#define SEND_DATA_CHECK   1        //Send data check flag bits //��������У���־λ
#define READ_DATA_CHECK   0        //Receive data to check flag bits //��������У���־λ
#define FRAME_HEADER      0X7B 		 //Frame_header //֡ͷ
#define FRAME_TAIL        0X7D 		 //Frame_tail   //֡β
#define SEND_DATA_SIZE    19	 		 //�������ݵ����ֽ�
#define RECEIVE_DATA_SIZE 15	 		 //�������ݵ����ֽ�
	

/*******The structure of the serial port sending data************/
/*******���ڷ������ݵĽṹ��*************************************/
typedef struct _SEND_DATA_  
{
	unsigned char buffer[SEND_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned char Frame_Header; //֡ͷ						//1 bytes
		unsigned char Flag; 				//Ԥ����־λ			//1 bytes
		unsigned char Status;				//Ԥ��״̬λ			//1 bytes
		short X_speed;	            //������X���ٶ� 	//2 bytes
		short Y_speed;              //������Y���ٶ�  	//2 bytes
		short Z_speed;              //������Z���ٶ�  	//2 bytes
		unsigned short LaserFront;	//ǰ��������		//2 bytes
		unsigned short LaserL;			//��༤����		//2 bytes
		unsigned short LaserR;			//�Ҳ༤����		//2 bytes
		unsigned short LaserRear;		//�󲿼�����		//2 bytes
		unsigned char Frame_Tail;   //֡β 						//1 bytes
	}Sensor_Str;
}SEND_DATA;	

/*******The structure of the serial port receiving data************/
/*******���ڽ������ݵĽṹ��*************************************/
typedef struct _RECEIVE_DATA_  
{
	unsigned char buffer[RECEIVE_DATA_SIZE];
	struct _Control_Str_
	{
		unsigned char Frame_Header; //֡ͷ						//1 bytes
		unsigned char Flag;					//Ԥ����־λ			//1 bytes
		unsigned char Status;				//Ԥ��״̬λ			//1 bytes
		short X_speed;	            //������X���ٶ� 	//2 bytes
		short Y_speed;              //������Y���ٶ�  	//2 bytes
		short Z_speed;              //������Z���ٶ�  	//2 bytes
		unsigned char Roller;				//���ƹ�Ͳ�Ƿ�����//1 bytes
		unsigned char Mode;					//С�����ģʽ����//1 bytes
		unsigned char KeepOrNot;		//����С���Ƿ����//1 bytes
		unsigned char PlaceOrNot;		//����С���Ƿ���//1 bytes
		unsigned char Frame_Tail;   //֡β 						//1 bytes
	}Control_Str;
}RECEIVE_DATA;


/*******The structure of the MACHINE_STATUS************/
/*******���ݽ��յĽṹ��*************************************/
typedef struct _ROBOT_CONTROL_  
{
	unsigned char Frame_Header; //֡ͷ						//1 bytes
	unsigned char Flag;					//Ԥ����־λ			//1 bytes
	unsigned char Status;				//Ԥ��״̬λ			//1 bytes
	short X_speed;	            //������X���ٶ� 	//2 bytes
	short Y_speed;              //������Y���ٶ�  	//2 bytes
	short Z_speed;              //������Z���ٶ�  	//2 bytes
	unsigned char Roller;				//���ƹ�Ͳ�Ƿ�����//1 bytes
	unsigned char Mode;					//С�����ģʽ����//1 bytes
	unsigned char KeepOrNot;		//����С���Ƿ����//1 bytes
	unsigned char PlaceOrNot;		//����С���Ƿ���//1 bytes
	unsigned char Frame_Tail;   //֡β 						//1 bytes
}ROBOT_CONTROL;


/*******The structure of the MACHINE_STATUS************/
/*******��е״̬�Ľṹ��*************************************/
typedef struct _MACHINE_STATUS_  
{
	unsigned char Roller;				//���ƹ�Ͳ�Ƿ�����//1 bytes
	unsigned char Mode;					//С�����ģʽ����//1 bytes
	unsigned char KeepOrNot;		//����С���Ƿ����//1 bytes
	unsigned char PlaceOrNot;		//����С���Ƿ���//1 bytes
}MACHINE_STATUS;
/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

/**************************Function declaration******************************/
/*******************************��������*************************************/
void message_task(void const * argument);			//FreeRtos��������
unsigned char Check_Sum(unsigned char Count_Number,unsigned char Mode);		//����У�麯��

//stm32������������λ��
void data_transition(void);					//���ݸ�ֵ����
void stm32_2_ros(void);							//�������Ϸ��ͺ���

//stm32������λ������
short received_data_trans(uint8_t Data_High, uint8_t Data_Low);		// ����ת������
void receive_data_from_ros(void);


extern SEND_DATA Send_Data;
extern RECEIVE_DATA Receive_Data;
extern MACHINE_STATUS Machine_Status;
extern ROBOT_CONTROL Robot_Control;

/* USER CODE END Prototypes */

#endif


