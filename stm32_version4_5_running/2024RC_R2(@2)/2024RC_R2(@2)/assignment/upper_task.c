/**
* Function       Сţ�ϲ㶯��
* @author        YH
* @date          2023.01.23
* @brief         FreeRTOS
* @retval        void
*/

#include "upper_task.h"
#include "message_task.h"
#include "chassis_task.h"
#include "gld_can.h"
#include "struct_typedef.h"
#include <math.h>

//��Ͳ2006������3508����
pid_type_def pid_3805_2006_speed[4];	
const fp32 PID_3805_2006_speed[3] ={10,0.5,5};  
int speed_3805_2006[3] ={0};

//�м�ͨ��3508
pid_type_def pid_passage_3508_speed[2];	
const fp32 PID_passage_3508_speed[3] ={10,2,5};  
int passage_3508_speed[2] ={0};
int flaggg[4]={0};

void tuqiu_duoji_set(int16_t value1,int16_t value2);
void xiqiu_duoji_set(int16_t value3,int16_t value4);
void upper_init(void);
void warehousing_control(void);
void read_key_pin(void);
void RollerButton(void);


void upper_task(void const * argument)
{
	upper_init();
	
	while(1)
	{	
		read_key_pin();
		RollerButton();
		warehousing_control();
//		osDelay(1);
	}	
}

void upper_init(void)
{
	tuqiu_duoji_set(2400,500);
	
	
	//����צ���ſ�
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);

	//����3508�͹�Ͳ2006
	for(i=0;i<=3;i++)
	{
	  PID_init(&pid_3805_2006_speed[i],PID_POSITION,PID_3805_2006_speed,16000,2000);  
	}
	
	//�м�ͨ��3508
	for(i=0;i<=1;i++)
	{
	  PID_init(&pid_passage_3508_speed[i],PID_POSITION,PID_passage_3508_speed,16000,5000);  
	}
	osDelay(20);
	
}


/***********************��ȡKEY1������ֵ********************************/
#define GPIO_KEY GPIOB					//�������š���>PB1
#define GPIO_KEY_PIN GPIO_PIN_1   

uint8_t read_key1;
uint8_t keyflag1=0;

void read_key_pin(void)
{
	read_key1=HAL_GPIO_ReadPin(GPIO_KEY,  GPIO_KEY_PIN);
	if(read_key1==GPIO_PIN_RESET)//�͵�ƽ������δ����
	{
		keyflag1=0;
	}
	if(read_key1==GPIO_PIN_SET)//�ߵ�ƽ����������
	{
		keyflag1=1;
	}
}


unsigned char flagC = 5;
unsigned char flagR = 1;
void RollerButton(void)
{
/*************************************�������****************************************/
	if(Robot_Control.Roller==1){	//ת��
		if(flagR ==1){
			speed_3805_2006[0] = 12000;       //��
      passage_3508_speed[0] = -2000;    //��
      passage_3508_speed[1] = -800;}    //��
		else if (flagR ==0){  // �� flagC ���� 1 �� 2 ʱ,��ת
			speed_3805_2006[0] = -13000;   //��
      passage_3508_speed[0] = 2000;  //��
      passage_3508_speed[1] = -900;} //��
	}	
	else{//��ֹ
		speed_3805_2006[0]=0;  
		passage_3508_speed[0]=0;  
		passage_3508_speed[1]=-900;
	}
}



void warehousing_control(void)
{
/*************************************���ҷ���****************************************/	
  if(Robot_Control.Mode==0)	
	{
		if(start_angle_record_can2[6]!=0&&start_angle_record_can2[7]!=0)
		{
			angle_gm3508[6] =0;      				
			angle_gm3508[7] =0;
		}	
		
		if(flagC == 5)
		{
			flagC = Robot_Control.KeepOrNot;
			if(flagC==1 || flagC==2){
				flagR=0;}
		}
		
		if(flagC==1)//������
		{
     	osDelay(800);
			if(start_angle_record_can2[4]!=0&&start_angle_record_can2[5]!=0){
				speed_3805_2006[2]=-1000;
				angle_gm3508[4] =8192*19.2*2;
				angle_gm3508[5] =-8192*19.2*2;
				osDelay(200);
				tuqiu_duoji_set(2400,2500);
				osDelay(500);
				flagC = 5;}
		}
		
		
		if(flagC==2)//������
		{
			osDelay(800);
			if(start_angle_record_can2[4]!=0&&start_angle_record_can2[5]!=0){
				speed_3805_2006[1]=1000;
				angle_gm3508[4] =8192*19.2*2;
				angle_gm3508[5] =-8192*19.2*2;
				osDelay(200);
				tuqiu_duoji_set(500,500);
				osDelay(500);
				flagC = 5;}
			
		}

		if(flagC==0)//��λ
		{
			osDelay(500);			
			tuqiu_duoji_set(2400,500);
			osDelay(500);
			if(start_angle_record_can2[4]!=0&&start_angle_record_can2[5]!=0)
			{
				angle_gm3508[4] =0;
				angle_gm3508[5] =0;
				speed_3805_2006[1] =0;
				speed_3805_2006[2] =0;
				flagC = 5;
				flagR =1;
			}		
		}	
	}
/*************************************��������****************************************/
	if(Robot_Control.Mode==1)
	{
		if(Robot_Control.PlaceOrNot==1)
			{
				#define Tolerance_1 8192*36*0.2
				if(start_angle_record_can2[4]!=0&&start_angle_record_can2[5]!=0&&start_angle_record_can2[6]!=0&&start_angle_record_can2[7]!=0)
					{
						osDelay(1000);
						//ץ�ּ���
						HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);
						osDelay(200);
						//ץ�ַ�ת
						angle_gm3508[6] =8192*36*0.42;      				
						angle_gm3508[7] =-8192*36*0.42;
						if((Cumulative_angle_can2[6]>=8192*36*0.42-Tolerance_1&&Cumulative_angle_can2[6]<=8192*36*0.42+Tolerance_1)&&(Cumulative_angle_can2[7]>=-8192*36*0.42-Tolerance_1&&Cumulative_angle_can2[7]<=-8192*36*0.42+Tolerance_1))
							{
								angle_gm3508[4] =8192*19.2*2;
								angle_gm3508[5] =-8192*19.2*2;
							}
					}		
			}
/*************************************�ſ��Ҹ�λ****************************************/			
		if(Robot_Control.PlaceOrNot==0)
			{
				#define Tolerance_2 1000
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);
				if(start_angle_record_can2[6]!=0&&start_angle_record_can2[7]!=0)
					{
						angle_gm3508[6] =0;      				
						angle_gm3508[7] =0;}			
					if((Cumulative_angle_can2[6]>=0-Tolerance_2&&Cumulative_angle_can2[6]<=0+Tolerance_2)&&(Cumulative_angle_can2[7]>=0-Tolerance_2&&Cumulative_angle_can2[7]<=0+Tolerance_2))
						{
							if(start_angle_record_can2[4]!=0&&start_angle_record_can2[5]!=0)
								{
									angle_gm3508[4] =0;
									angle_gm3508[5] =0;
								}
						}
			}
	}
}
///*************************************�ſ��Ҹ�λ****************************************/	
//		if(Receive_Data.buffer[12]==0){
//		#define Tolerance_2 1000
//		flaggg[0] =2;
//		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);
//		if(start_angle_record_can2[6]!=0&&start_angle_record_can2[7]!=0)
//		{
//			angle_gm3508[6] =0;      				
//			angle_gm3508[7] =0;
//		}			
//		if((Cumulative_angle_can2[6]>=0-Tolerance_2&&Cumulative_angle_can2[6]<=0+Tolerance_2)&&(Cumulative_angle_can2[7]>=0-Tolerance_2&&Cumulative_angle_can2[7]<=0+Tolerance_2))
//		{
//			 if(start_angle_record_can2[4]!=0&&start_angle_record_can2[5]!=0)
//			{
//				angle_gm3508[4] =0;
//				angle_gm3508[5] =0;
//			}
//		}
//   
//	}
	
//}


void tuqiu_duoji_set(int16_t value1,int16_t value2)
{
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,value1);  //�������ʼֵ2400  S
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,value2);   //�Ҳ�����ʼֵ500  T
}

void xiqiu_duoji_set(int16_t value3,int16_t value4)
{
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,value3);  //�������ʼֵ2500  U
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,value4);   //�Ҳ�����ʼֵ500  V
}
