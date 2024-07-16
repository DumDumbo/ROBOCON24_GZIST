/**
* Function       
* @author        YH
* @date          2023.01.23
* @brief         FreeRTOS
* @retval        void
*/

/* USER CODE BEGIN Includes */
#include "usart.h"
#include "message_task.h"
#include "chassis_task.h"
#include "upper_task.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PV */

//�����ṹ�����
SEND_DATA Send_Data;
RECEIVE_DATA Receive_Data;
MACHINE_STATUS Machine_Status;
ROBOT_CONTROL Robot_Control;

//ȫ�ֱ�������
uint8_t Interrupt_Buffer[1];

/* USER CODE END PV */


/* USER CODE BEGIN 0 */
/**************************************************************************
Function: void message_task(void const * argument)
Input   : void const * argument
Output  : none
�������ܣ�FreeRtos�����������β����жϽ��գ�������Ϊ�գ�
��ڲ�����void const * argument
����  ֵ����
**************************************************************************/
void message_task(void const * argument)
{
	//����ͨѶ����
	  HAL_UART_Receive_IT(&huart3,Interrupt_Buffer,sizeof(Interrupt_Buffer));  //���������ж�
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);  
	
	while(1)
	{
		//�����Ϸ�����
		stm32_2_ros();
		
		// ������λ��ͨ���йأ�������״̬������ʱ��С���ٶȸ�ֵΪ0����ֹС���Ҵ�
		if (HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY &&
			HAL_UART_GetState(&huart3) != HAL_UART_STATE_RESET &&
			HAL_UART_GetState(&huart3) != HAL_UART_STATE_TIMEOUT &&
			HAL_UART_GetState(&huart3) != HAL_UART_STATE_ERROR) 
		{
			Receive_Data.Control_Str.X_speed = 0;							//С��X�����ٶȣ�ROS����ϵ��
			Receive_Data.Control_Str.Y_speed = 0;							//С��Y�����ٶȣ�ROS����ϵ��
			Receive_Data.Control_Str.Z_speed = 0;							//С��Z����ٶȣ�ROS����ϵ��
		}
	}

}

/**************************************************************************
Function: The data sent by the serial port is assigned
Input   : none
Output  : none
�������ܣ����ڷ��͵����ݽ��и�ֵ
��ڲ�������
����  ֵ����
**************************************************************************/
void data_transition(void)
{
	//��ȡ��Ҫ���͵����ݵ�ֵ
	Send_Data.Sensor_Str.Frame_Header = FRAME_HEADER; 		//Frame_header //֡ͷ
	Send_Data.Sensor_Str.Frame_Tail = FRAME_TAIL;     		//Frame_tail //֡β
	Send_Data.Sensor_Str.Flag = keyflag1;												//��־λ
	Send_Data.Sensor_Str.Status = 1;											//��־λ
	Send_Data.Sensor_Str.X_speed = (int)actual_speed[0];	//С��X�����ٶȣ�ROS����ϵ��
	Send_Data.Sensor_Str.Y_speed = (int)actual_speed[1];	//С��Y�����ٶȣ�ROS����ϵ��
	Send_Data.Sensor_Str.Z_speed = (int)actual_speed[2];	//С��Z����ٶȣ�ROS����ϵ��
	Send_Data.Sensor_Str.LaserFront = data_10_usatr2;			//ǰ�����������ݣ��Գ�ͷ����Ϊ��׼��
	Send_Data.Sensor_Str.LaserL = data_10_usatr6;					//��༤��������
	Send_Data.Sensor_Str.LaserR = data_10_usatr7;					//�Ҳ༤��������
	Send_Data.Sensor_Str.LaserRear = data_10_usatr8;			//�󲿼���������
	
	//Ϊ��Ҫ���͵����ݸ�ֵ
	Send_Data.buffer[0] = Send_Data.Sensor_Str.Frame_Header; 			//��һλ֡ͷ
	Send_Data.buffer[1] = Send_Data.Sensor_Str.Flag;							//��־λ		
	Send_Data.buffer[2] = Send_Data.Sensor_Str.Status;						//��־λ
	//The three-axis speed of / / car is split into two eight digit Numbers
	//С�������ٶ�,���ᶼ���Ϊ����8λ�����ٷ���
	Send_Data.buffer[3]=Send_Data.Sensor_Str.X_speed >> 8;  			//X��߰�λ
	Send_Data.buffer[4]=Send_Data.Sensor_Str.X_speed & 0xFF;     	//X��Ͱ�λ
	Send_Data.buffer[5]=Send_Data.Sensor_Str.Y_speed >> 8;  
	Send_Data.buffer[6]=Send_Data.Sensor_Str.Y_speed & 0xFF;   
	Send_Data.buffer[7]=Send_Data.Sensor_Str.Z_speed >> 8;   
	Send_Data.buffer[8]=Send_Data.Sensor_Str.Z_speed & 0xFF;  
	//���Ҽ��������ݸ�ֵ
	Send_Data.buffer[9]=Send_Data.Sensor_Str.LaserL >> 8;        // ��������ݸ߰�λ
	Send_Data.buffer[10]=Send_Data.Sensor_Str.LaserL & 0xFF;   	 // ��������ݵͰ�λ
	Send_Data.buffer[11]=Send_Data.Sensor_Str.LaserR >> 8;       // �Ҳ������ݸ߰�λ
	Send_Data.buffer[12]=Send_Data.Sensor_Str.LaserR & 0xFF;   	 // �Ҳ������ݵͰ�λ
	
	Send_Data.buffer[13]=Send_Data.Sensor_Str.LaserFront >> 8;   // ǰ��������ݸ߰�λ
	Send_Data.buffer[14]=Send_Data.Sensor_Str.LaserFront & 0xFF; // ǰ��������ݵͰ�λ
	Send_Data.buffer[15]=Send_Data.Sensor_Str.LaserRear >> 8;    // �󲿲�����ݸ߰�λ
	Send_Data.buffer[16]=Send_Data.Sensor_Str.LaserRear & 0xFF;  // �󲿲�����ݵͰ�λ
	
  //Data check digit calculation, Pattern 1 is a data check
  //����У��λ���㣬ģʽ1�Ƿ�������У��
	Send_Data.buffer[17]=Check_Sum(17,1);   
	
	Send_Data.buffer[18]=Send_Data.Sensor_Str.Frame_Tail; //Frame_tail //֡β
}

/**************************************************************************
Function: Send data to host computer
Input   : none
Output  : none
�������ܣ����ڷ��ͺ���
��ڲ�������
�� �� ֵ����
**************************************************************************/
void stm32_2_ros(void)
{
	//���ݸ�ֵ
	data_transition();
	//�������Ϸ���
	for(unsigned char i = 0; i<SEND_DATA_SIZE;i++)
	{
		
		/*��һ�ַ��ͺ�����HAL_UART_Transmit����һ����������������ȴ��������ݱ�������ɺ�ŷ��ء�
																				 �������ڶ��ڡ���Ƶ�ʵķ��Ͳ�����
				������huart��		UART�����
							pData��		ָ�������ݻ�������ָ�롣
							Size��		Ҫ���͵������ֽ�����
							Timeout��	���ͳ�ʱʱ�䡣
			 ����ֵ��
							return��	���ظú���ִ��״̬��*/
		
//			HAL_UART_Transmit(&huart1,(uint8_t*)&Send_Data.buffer[i],sizeof(Send_Data.buffer[i]),1);
//			HAL_Delay(1);	
	
		/*�ڶ��ַ��ͺ�����HAL_UART_Transmit_IT����һ���������ĺ����������������ز��ں�̨ͨ���ж���������ݵķ��͡�
																						�����ڴ������Ƶ�ʵ����ݴ��䣬��Ϊ�����������������ִ�С�
				������huart��		UART�����
							pData��		ָ�������ݻ�������ָ�롣
							Size��		Ҫ���͵������ֽ�����
			����ֵ��
							return��	���ظú���ִ��״̬��*/	

			HAL_UART_Transmit_IT(&huart3,(uint8_t*)&Send_Data.buffer[i],sizeof(Send_Data.buffer[i]));
			HAL_Delay(1);
		/*�����ַ��ͺ�����HAL_UART_Transmit_DMA���Ƿ������ģ���Ϊ���ݴ�����ͨ��DMA���еģ�����ҪCPU��ֱ�Ӳ��롣
																						 ��������һ�� HAL_StatusTypeDef ö�٣���ʾ������ִ��״̬��
				������huart��		UART�����
							pData��		ָ�������ݻ�������ָ�롣
							Size��		Ҫ���͵������ֽ�����
			����ֵ��
							return��	���ظú���ִ��״̬��*/

//			HAL_UART_Transmit_DMA(&huart8,(uint8_t*)&Send_Data.buffer[i],sizeof(Send_Data.buffer[i]));
//			HAL_Delay(1);
			
		}

}

/**************************************************************************
Function: Calculates the check bits of data to be sent/received
Input   : Count_Number: The first few digits of a check; Mode: 0-Verify the received data, 1-Validate the sent data
Output  : Check result
�������ܣ�����Ҫ����/���յ�����У����
��ڲ�����Count_Number��У���ǰ��λ����Mode��0-�Խ������ݽ���У�飬1-�Է������ݽ���У��
����  ֵ��У����
**************************************************************************/
unsigned char Check_Sum(unsigned char Count_Number,unsigned char Mode)
{
	unsigned char check_sum=0,k;
	
	//Validate the data to be sent
	//��Ҫ���͵����ݽ���У��
	if(Mode==1)
	for(k=0;k<Count_Number;k++)
	{
		check_sum=check_sum^Send_Data.buffer[k];
	}
	
	//Verify the data received
	//�Խ��յ������ݽ���У��
	if(Mode==0)
	for(k=0;k<Count_Number;k++)
	{
		check_sum=check_sum^Receive_Data.buffer[k];
	}
	return check_sum;
}

/**************************************************************************
Function: Receive data from host computer
Input   : none
Output  : none
�������ܣ����ڽ��պ���
��ڲ�������
�� �� ֵ����
ע	  �⣺ѡ�õ����ݽ��պ�������main.c�ĺ���UserCodeBegin2�У��������жϻص������д���
**************************************************************************/
void receive_data_from_ros()
{
	
	/*��һ�ֽ��պ�����HAL_UART_Receive()�� ͨ����ѯ��ʽʵ�֣���������һֱ�ȴ�ֱ�����յ�ָ�����������ݻ�ʱ��
																			 �����ڼ򵥵Ĵ��ڽ��ղ����������ܻᵼ��CPU�Ŀ���ʱ���˷��ڵȴ����������ϡ�
				������huart��		UART�����
							pData��		ָ��洢�������ݵĻ�������ָ�롣��
							Size��		Ҫ���յ������ֽ�����
							Timeout��	���ճ�ʱʱ�䡣
			 ����ֵ��
							return��	���ظú���ִ��״̬��*/
		
//			HAL_UART_Receive(&huart1,(uint8_t*)Receive_Data.buffer[i],sizeof(Receive_Data.buffer[i]),1);
//			HAL_Delay(1);	
	
		/*�ڶ��ֽ��պ�����HAL_UART_Receive_IT����һ���������ĺ�����ͨ���жϷ�ʽʵ�֣�������������������أ�
																						�������ʱ�ᴥ���жϻص������������������������ִ�С�
				������huart��		UART�����
							pData��		ָ��洢�������ݵĻ�������ָ�롣
							Size��		Ҫ���յ������ֽ�����
			����ֵ��
							return��	���ظú���ִ��״̬��*/	

//			HAL_UART_Receive_IT(&huart1,(uint8_t*)Receive_Data.buffer,sizeof(Receive_Data.buffer));
//			HAL_Delay(1);
			
		/*�����ֽ��պ�����HAL_UART_Receive_DMA���������ģ�ͨ��DMA��ʽʵ�֣�������������������أ��������ʱ�ᴥ��DMA��������жϡ�
																						 ��������һ�� HAL_StatusTypeDef ö�٣���ʾ������ִ��״̬��
				������huart��		UART�����
							pData��		ָ��洢�������ݵĻ�������ָ�롣
							Size��		Ҫ���յ������ֽ�����
			����ֵ��
							return��	���ظú���ִ��״̬��*/

//			HAL_UART_Receive_DMA(&huart1,Receive_Data.buffer,100)��
//			HAL_Delay(1);
				 
}

/**************************************************************************
Function: Receive data transformation
Input   : uint8_t Data_High, uint8_t Data_Low
Output  : short transition_16
�������ܣ�������8λ����ƴ��Ϊ16λ
��ڲ������߰�λ���ݣ��Ͱ�λ����
�� �� ֵ��16λ���� transition����16
**************************************************************************/
short received_data_trans(uint8_t Data_High, uint8_t Data_Low)
{
	short transition_16=0;   // ����ת���м����
  transition_16 |=  Data_High << 8; //Get the high 8 bits of data   // ����8λ��������8λ����߰�λ������������
  transition_16 |=  Data_Low;      //Get the lowest 8 bits of data //��ȡ���ݵĵ�8λ�����8λ������������
	return transition_16;
}


/**************************************************************************
Function: UART8_Callback_Function
Input   : none
Output  : none
�������ܣ�HAL_UART_Receive_IT���жϻص�����������Ϊ1�ֽڣ�
					�Դ��ڽ��յ����ݽ������ϸ�ֵ
��ڲ�������
�� �� ֵ����
**************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
	{
		
		if(huart == &huart3) // ����Ǵ���3
		{
		
			uint8_t check=0,error=1;	//Temporary variable to save the data of the lower machine //��ʱ������������λ������
			static int count; 				//Static variable for counting //��̬���������ڼ�������̬�����������������������������ڼ�
	
	
			// �̶�ֵ���ݸ�ֵ
			Receive_Data.buffer[count] = Interrupt_Buffer[0]; //Fill the array with serial data //����������������
			Receive_Data.Control_Str.Frame_Header = Receive_Data.buffer[0]; 	//The first part of the data is the frame header 0X7B //���ݵĵ�һλ��֡ͷ0X7B
			Receive_Data.Control_Str.Frame_Tail = Receive_Data.buffer[14];  	//The last bit of data is frame tail 0X7D //���ݵ����һλ��֡β0X7D
			
			//����ƥ��
			//Ensure that the first data in the array is FRAME_HEADER //ȷ�������һ������ΪFRAME_HEADER
			if(Interrupt_Buffer[0] == FRAME_HEADER || count>0)
				count++;
			else
				count = 0;
	
			if(count == RECEIVE_DATA_SIZE) //Verify the length of the packet //��֤���ݰ��ĳ���
				{
					//��λcount
					count=0;  //Prepare for the serial port data to be refill into the array //Ϊ����������������������׼��
			
				if(Receive_Data.Control_Str.Frame_Tail == FRAME_TAIL) //Verify the frame tail of the packet //��֤���ݰ���֡β
					{
						check=Check_Sum(13,READ_DATA_CHECK);  //BCC check passes or two packets are interlaced //BCCУ��ͨ�������������ݰ�����
					}
				 
				if(check == Receive_Data.buffer[13])   	// ƥ��У��λ
					{
						error=0;  //XOR bit check successful //���λУ��ɹ�
					}
				
				if(error == 0)			//�޴���ʼ���ݸ�ֵƴ��
					{
						Robot_Control.Flag = Receive_Data.buffer[1];    //Ԥ��λFlag
						Robot_Control.Status = Receive_Data.buffer[2];	 //Ԥ��λStatus
						Robot_Control.X_speed = received_data_trans(Receive_Data.buffer[3],Receive_Data.buffer[4]);
						Robot_Control.Y_speed = received_data_trans(Receive_Data.buffer[5],Receive_Data.buffer[6]);
						Robot_Control.Z_speed = received_data_trans(Receive_Data.buffer[7],Receive_Data.buffer[8]);
						Robot_Control.Roller = Receive_Data.buffer[9];
						Robot_Control.Mode = Receive_Data.buffer[10];
						Robot_Control.KeepOrNot = Receive_Data.buffer[11];
						Robot_Control.PlaceOrNot = Receive_Data.buffer[12];
					}			
				}
			// ������������3�Ľ����жϣ�׼����һ�ν���
      HAL_UART_Receive_IT(&huart3, Interrupt_Buffer, sizeof(Interrupt_Buffer));
			}
	}


/* USER CODE END 0 */
	
	

