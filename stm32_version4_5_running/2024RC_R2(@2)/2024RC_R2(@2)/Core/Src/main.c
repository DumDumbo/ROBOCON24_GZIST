/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "gld_can.h"
#include "struct_typedef.h"
#include "gld_can.h"
#include "pid.h"
#include "chassis_task.h"


/*USART2********************************************************/
int data_10_usatr2 = 0;
uint8_t len_usatr2;
uint8_t rx_buffer_usatr2[30];               //接收数据的数组
volatile uint8_t rx_len_usatr2 = 0;          //接收数据的长度
volatile uint8_t recv_end_flag_usatr2 = 0;   //接收结束标志位
unsigned char date_l1_usatr2[5] ={0};


/*USART3********************************************************/
//int data_10_usatr3 = 0;
//uint8_t rx_buffer_usatr3[100];               //接收数据的数组
//volatile uint8_t rx_len_usatr3 = 0;          //接收数据的长度
//volatile uint8_t recv_end_flag_usatr3 = 0;   //接收结束标志位

//void usart_printf_usart3(const char *fmt,...)
//{
//	static uint8_t tx_buf_usart3[256] = {0};
//	static va_list ap;
//	static uint16_t len_usart3;
//	va_start(ap, fmt);
//	len_usart3 = vsprintf((char *)tx_buf_usart3, fmt, ap);
//	va_end(ap);
//	HAL_UART_Transmit_DMA(&huart3,tx_buf_usart3, len_usart3);
//}

/*USART6********************************************************/
int data_10_usatr6 = 0;
uint8_t singal = 0;
uint8_t len_usatr6;
uint8_t rx_buffer_usatr6[30];               //接收数据的数组
volatile uint8_t rx_len_usatr6 = 0;          //接收数据的长度
volatile uint8_t recv_end_flag_usatr6 = 0;   //接收结束标志位
unsigned char date_l1_usatr6[5] ={0};
int yaw_angle =0;

void usart_printf_usart6(const char *fmt,...)
{
	static uint8_t tx_buf[256] = {0};
	static va_list ap;
	static uint16_t len;
	va_start(ap, fmt);
	len = vsprintf((char *)tx_buf, fmt, ap);
	va_end(ap);
	HAL_UART_Transmit_DMA(&huart6,tx_buf, len);
	
}

/*USART7********************************************************/
int data_10_usatr7 = 0;
uint8_t len_usatr7;
uint8_t rx_buffer_usatr7[30];               //接收数据的数组
volatile uint8_t rx_len_usatr7 = 0;          //接收数据的长度
volatile uint8_t recv_end_flag_usatr7 = 0;   //接收结束标志位
unsigned char date_l1_usatr7[5] ={0};


/*USART8********************************************************/
int data_10_usatr8 = 0;
uint8_t len_usatr8;
uint8_t rx_buffer_usatr8[30];               //接收数据的数组
volatile uint8_t rx_len_usatr8 = 0;          //接收数据的长度
volatile uint8_t recv_end_flag_usatr8 = 0;   //接收结束标志位
unsigned char date_l1_usatr8[5] ={0};

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
RC_Ctl_t RC_Ctl;   					//声明遥控器数据结构体
uint8_t sbus_rx_buffer[18]; 		//声明遥控器缓存数组
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_USART6_UART_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_UART7_Init();
  MX_UART8_Init();
  MX_USART3_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  can_filter_init();
  HAL_UART_Receive_DMA(&huart1,sbus_rx_buffer,18);
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
  
  /*USART2********************************************************/
  __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);  //开启空闲中断
  HAL_UART_Receive_DMA(&huart2,rx_buffer_usatr2,30);  //开启DMA接收中断
	 
  /*USART6********************************************************/
  HAL_UART_Receive_DMA(&huart6,rx_buffer_usatr6,30);  //开启DMA接收中断
  __HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);  
 
  /*USART7********************************************************/
  __HAL_UART_ENABLE_IT(&huart7, UART_IT_IDLE);  //开启空闲中断
  HAL_UART_Receive_DMA(&huart7,rx_buffer_usatr7,30);  //开启DMA接收中断

  /*USART8********************************************************/
  __HAL_UART_ENABLE_IT(&huart8, UART_IT_IDLE);  //开启空闲中断
  HAL_UART_Receive_DMA(&huart8,rx_buffer_usatr8,30);  //开启DMA接收中断
  
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_2, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_3, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_4, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_5, GPIO_PIN_SET);
  
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);
  /*定时器2*/
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);//串口		S
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);//串口		T
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);//串口		V
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);//串口		Y
  
  /*定时器4*/
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);//串口		H
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);//串口		G
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);//串口		F
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);//串口		E
  
  HAL_UART_Transmit_IT(&huart2, "iFACM",5);
	HAL_UART_Transmit_DMA(&huart6, "iFACM",5);
	HAL_UART_Transmit_DMA(&huart7, "iFACM",5);
	HAL_UART_Transmit_DMA(&huart8, "iFACM",5);
  HAL_Delay(200); 
  
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) 
//{  
//  RC_Ctl.rc.ch0 = (sbus_rx_buffer[0]| (sbus_rx_buffer[1] << 8)) & 0x07ff;          
//	RC_Ctl.rc.ch1 = ((sbus_rx_buffer[1] >> 3) | (sbus_rx_buffer[2] << 5)) & 0x07ff;       
//	RC_Ctl.rc.ch2 = ((sbus_rx_buffer[2] >> 6) | (sbus_rx_buffer[3] << 2) | (sbus_rx_buffer[4] << 10)) & 0x07ff;          
//	RC_Ctl.rc.ch3 = ((sbus_rx_buffer[4] >> 1) | (sbus_rx_buffer[5] << 7)) & 0x07ff;           
//	RC_Ctl.rc.s1  = ((sbus_rx_buffer[5] >> 4)& 0x000C) >> 2;                           
//	RC_Ctl.rc.s2  = ((sbus_rx_buffer[5] >> 4)& 0x0003);  
//  RC_Ctl.rc.sw=sbus_rx_buffer[16]|(sbus_rx_buffer[17]<<8);	
//	
//	RC_Ctl.mouse.x = sbus_rx_buffer[6] | (sbus_rx_buffer[7] << 8);                    //!< Mouse X axis        
//	RC_Ctl.mouse.y = sbus_rx_buffer[8] | (sbus_rx_buffer[9] << 8);                    //!< Mouse Y axis      
//	RC_Ctl.mouse.z = sbus_rx_buffer[10] | (sbus_rx_buffer[11] << 8);                  //!< Mouse Z axis         
//	RC_Ctl.mouse.press_l = sbus_rx_buffer[12];                                        //!< Mouse Left Is Press      
//	RC_Ctl.mouse.press_r = sbus_rx_buffer[13];                                        //!< Mouse Right Is Press 
//	RC_Ctl.key.v = sbus_rx_buffer[14] | (sbus_rx_buffer[15] << 8);   			            //!< KeyBoard value
//	
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
