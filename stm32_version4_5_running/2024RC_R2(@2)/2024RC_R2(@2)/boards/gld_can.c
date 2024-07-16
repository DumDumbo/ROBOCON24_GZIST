/**
* Function       CAN1和CAN2接收和发送
* @author        YH
* @date          2024.01.22
* @brief         can_filter_init&&CAN_send
* @retval        void
*/

#include "gld_can.h"
#include "main.h"
#include <math.h>

/*GM6020角度累计*/
long int Cumulative_angle_can1[8]={0};
int16_t Cumulative_angle_start_flag_can1[8] ={0};
int16_t start_angle_flag_can1 =0;
int16_t start_angle_record_can1[8] ={0};

long int Cumulative_angle_can2[8]={0};
int16_t Cumulative_angle_start_flag_can2[8] ={0};
int16_t start_angle_flag_can2 =0;
int16_t start_angle_record_can2[8] ={0};


extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

#define get_motor_measure(ptr, data)                                    \
    {                                                                   \
        (ptr)->last_ecd = (ptr)->ecd;                                   \
        (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);            \
        (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);      \
        (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]);  \
        (ptr)->temperate = (data)[6];                                   \
    }
	
motor_measure_t motor_date_can1[8];
motor_measure_t motor_date_can2[8];
	
static CAN_TxHeaderTypeDef  chassis_tx_message;
static uint8_t              chassis_can_send_data[8];

/*显示CAN1和CAN2的id*/
uint8_t CAN1_ID =0;
uint8_t CAN2_ID =0;

	
/*配置can1和can2的过滤器*/
void can_filter_init(void)
{
    CAN_FilterTypeDef can_filter_st_1;
    can_filter_st_1.FilterActivation = ENABLE;
    can_filter_st_1.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st_1.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st_1.FilterIdHigh = 0x0000;
    can_filter_st_1.FilterIdLow = 0x0000;
    can_filter_st_1.FilterMaskIdHigh = 0x0000;
    can_filter_st_1.FilterMaskIdLow = 0x0000;
    can_filter_st_1.FilterBank = 0;
	
    can_filter_st_1.FilterFIFOAssignment = CAN_RX_FIFO0;
	
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st_1);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);


	
    CAN_FilterTypeDef can_filter_st_2;
    can_filter_st_2.FilterActivation = ENABLE;
    can_filter_st_2.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st_2.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st_2.FilterIdHigh = 0x0000;
    can_filter_st_2.FilterIdLow = 0x0000;
    can_filter_st_2.FilterMaskIdHigh = 0x0000;
    can_filter_st_2.FilterMaskIdLow = 0x0000;

    can_filter_st_2.SlaveStartFilterBank = 14;
    can_filter_st_2.FilterBank = 14;
	
    can_filter_st_2.FilterFIFOAssignment = CAN_RX_FIFO0;
	
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st_2);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}

/*hcanx是选择can1，can2（han1&han2）SSID是标识符的选择（0x200&0x1FF&0x2FF）*/
void CAN_send(CAN_HandleTypeDef hcanx,int16_t SSID,int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
    uint32_t send_mail_box;
    chassis_tx_message.StdId = SSID;
    chassis_tx_message.IDE = CAN_ID_STD;
    chassis_tx_message.RTR = CAN_RTR_DATA;
    chassis_tx_message.DLC = 0x08;
    chassis_can_send_data[0] = motor1 >> 8;
    chassis_can_send_data[1] = motor1;
    chassis_can_send_data[2] = motor2 >> 8;
    chassis_can_send_data[3] = motor2;
    chassis_can_send_data[4] = motor3 >> 8;
    chassis_can_send_data[5] = motor3;
    chassis_can_send_data[6] = motor4 >> 8;
    chassis_can_send_data[7] = motor4;

    HAL_CAN_AddTxMessage(&hcanx, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}

/*主can1和从can2共同接收使用*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == CAN1)
	{
		CAN_RxHeaderTypeDef rx_header_can1;
		uint8_t rx_data_can1[8];

		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header_can1, rx_data_can1);

		switch (rx_header_can1.StdId)
		{
			case 0x201:
			case 0x202:
			case 0x203:
			case 0x204:
			case 0x205:
			case 0x206:
			case 0x207:
			case 0x208:
			{
				CAN1_ID = rx_header_can1.StdId - 0x201;
				get_motor_measure(&motor_date_can1[CAN1_ID], rx_data_can1);
				angle_total_can1(CAN1_ID);
								
				break;
			}

			default:
			{
				break;
			}
		}		
	}
	

	
	if(hcan->Instance == CAN2)
	{
		CAN_RxHeaderTypeDef rx_header_can2;
		uint8_t rx_data_can2[8];

		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header_can2, rx_data_can2);

		switch (rx_header_can2.StdId)
		{
			case 0x201:
			case 0x202:
			case 0x203:
			case 0x204:
			case 0x205:
			case 0x206:
			case 0x207:
			case 0x208:
			{
				CAN2_ID = rx_header_can2.StdId - 0x201;
				get_motor_measure(&motor_date_can2[CAN2_ID], rx_data_can2);
				angle_total_can2(CAN2_ID);
				
				break;
			}

			default:
			{
				break;
			}
		}				
	}
}

const motor_measure_t *get_motor_message_can1(uint8_t i)
{
    return &motor_date_can1[i];
}

const motor_measure_t *get_motor_message_can2(uint8_t i)
{
    return &motor_date_can2[i];
}

/*电机角度累计，用于位置环和累计圈数目进行使用*/
void angle_total_can1(uint8_t i)
{
	if(motor_date_can1[i].ecd==motor_date_can1[i].last_ecd)
	{
		if(Cumulative_angle_start_flag_can1[i] ==0)
		{
			start_angle_record_can1[i] =motor_date_can1[i].ecd;
			Cumulative_angle_can1[i] =0;
		}
		Cumulative_angle_start_flag_can1[i] =1;
	}
	
	if(Cumulative_angle_start_flag_can1[i] ==1)
	{
		if(fabs(motor_date_can1[i].ecd - motor_date_can1[i].last_ecd) > 4095)                                 //现在的ecd小于上一下的ecd且过了半圈，说明本次过了零点
		{	
			if(motor_date_can1[i].ecd < motor_date_can1[i].last_ecd )                                        //过了半圈且过了零点
			{
				Cumulative_angle_can1[i] += (8191 - motor_date_can1[i].last_ecd + motor_date_can1[i].ecd);   	               //已经转到下一圈，则累计转过8192(1圈)上一次+本次
			}
			else
			{			      
				Cumulative_angle_can1[i] -= (8191 - motor_date_can1[i].ecd + motor_date_can1[i].last_ecd);				   //超过一圈
			}
		}

		else
		{			
			  Cumulative_angle_can1[i] += (motor_date_can1[i].ecd - motor_date_can1[i].last_ecd);						   //未过临界值,累加转过的角度差
		}		
		
	}

}

void angle_total_can2(uint8_t i)
{
	if(motor_date_can2[i].ecd==motor_date_can2[i].last_ecd)
	{
		if(Cumulative_angle_start_flag_can2[i] ==0)
		{
			start_angle_record_can2[i] =motor_date_can2[i].ecd;
			Cumulative_angle_can2[i] =0;
		}
		Cumulative_angle_start_flag_can2[i] =1;
	}
	
	if(Cumulative_angle_start_flag_can2[i] ==1)
	{
		if(fabs(motor_date_can2[i].ecd - motor_date_can2[i].last_ecd) > 4095)                                 //现在的ecd小于上一下的ecd且过了半圈，说明本次过了零点
		{	
			if(motor_date_can2[i].ecd < motor_date_can2[i].last_ecd )                                        //过了半圈且过了零点
			{
				Cumulative_angle_can2[i] += (8191 - motor_date_can2[i].last_ecd + motor_date_can2[i].ecd);   	               //已经转到下一圈，则累计转过8192(1圈)上一次+本次
			}
			else
			{			      
				Cumulative_angle_can2[i] -= (8191 - motor_date_can2[i].ecd + motor_date_can2[i].last_ecd);				   //超过一圈
			}
		}

		else
		{			
			  Cumulative_angle_can2[i] += (motor_date_can2[i].ecd - motor_date_can2[i].last_ecd);						   //未过临界值,累加转过的角度差
		}		
		
	}
//	uint8_t i =0;
//	if(start_angle_flag_can2 ==0)
//	{
//		for(i =0;i<8;i++)
//		{
//			start_angle_record_can2[i] = motor_date_can2[i].ecd;
//		}
//        if(start_angle_record_can2[4] !=0)
//		{
//			angle_6020 =start_angle_record_can2[4];
//			start_angle_flag_can2 =1;
//		}			
//	}

//	if(motor_date_can2[4].ecd==motor_date_can2[4].last_ecd)
//	{
//		Cumulative_angle_start_flag_can2 =1;
//	}
//	
//	if(Cumulative_angle_start_flag_can2 ==1)
//	{
//		for(i=0;i<8;i++)
//		{
//			if(fabs(motor_date_can2[i].ecd - motor_date_can2[i].last_ecd) > 4095)                                 //现在的ecd小于上一下的ecd且过了半圈，说明本次过了零点
//			{	
//				if(motor_date_can2[i].ecd < motor_date_can2[i].last_ecd )                                        //过了半圈且过了零点
//				{
//					Cumulative_angle_can2[i] += (8191 - motor_date_can2[i].last_ecd + motor_date_can2[i].ecd);   	               //已经转到下一圈，则累计转过8192(1圈)上一次+本次
//				}
//				else
//				{			      
//					Cumulative_angle_can2[i] -= (8191 - motor_date_can2[i].ecd + motor_date_can2[i].last_ecd);				   //超过一圈
//				}
//			}

//			else
//			{			
//				  Cumulative_angle_can2[i] += (motor_date_can2[i].ecd - motor_date_can2[i].last_ecd);						   //未过临界值,累加转过的角度差
//			}		
//		}		
//	}

}
