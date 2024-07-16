/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct
{
	struct
	{ 
		unsigned short ch0;
		unsigned short ch1;
		unsigned short ch2;
		unsigned short ch3;
		unsigned char s1;
		unsigned char s2;
		unsigned short sw;
	}rc;
	
	struct 
	{
		unsigned short x;
		unsigned short y;
		unsigned short z;
		unsigned char press_l;
		unsigned char press_r;
	}mouse;
	
	struct
	{
		unsigned short v;
	}key;
}RC_Ctl_t;

/*遥控器SBUS********************************************************/
extern RC_Ctl_t RC_Ctl;   		     //声明遥控器数据结构体
extern uint8_t sbus_rx_buffer[18];   //声明遥控器缓存数组


/*USART2********************************************************/
extern int data_10_usatr2;
extern uint8_t rx_buffer_usatr2[30];           //接收数据的数组
extern volatile uint8_t rx_len_usatr2;          //接收数据的长度
extern volatile uint8_t recv_end_flag_usatr2;   //接收结束标志位
extern unsigned char date_l1_usatr2[5];


/*USART3********************************************************/
extern int data_10_usatr3;
extern uint8_t rx_buffer_usatr3[30];           //接收数据的数组
extern volatile uint8_t rx_len_usatr3;          //接收数据的长度
extern volatile uint8_t recv_end_flag_usatr3;   //接收结束标志位
extern void usart_printf_usart3(const char *fmt,...);

/*USART6********************************************************/
extern int data_10_usatr6;
extern uint8_t singal;
extern uint8_t rx_buffer_usatr6[30];           //接收数据的数组
extern volatile uint8_t rx_len_usatr6;          //接收数据的长度
extern volatile uint8_t recv_end_flag_usatr6;   //接收结束标志位
extern unsigned char date_l1_usatr6[5];
extern int yaw_angle;
extern void usart_printf(const char *fmt,...);


/*USART7********************************************************/
extern int data_10_usatr7;
extern uint8_t rx_buffer_usatr7[30];           //接收数据的数组
extern volatile uint8_t rx_len_usatr7;          //接收数据的长度
extern volatile uint8_t recv_end_flag_usatr7;   //接收结束标志位
extern unsigned char date_l1_usatr7[5];

/*USART8********************************************************/
extern int data_10_usatr8;
extern uint8_t rx_buffer_usatr8[30];           //接收数据的数组
extern volatile uint8_t rx_len_usatr8;          //接收数据的长度
extern volatile uint8_t recv_end_flag_usatr8;   //接收结束标志位
extern unsigned char date_l1_usatr8[5];

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
