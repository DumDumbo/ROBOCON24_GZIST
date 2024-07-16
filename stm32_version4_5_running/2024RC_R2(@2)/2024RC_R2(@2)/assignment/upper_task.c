/**
* Function       小牛上层动作
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

//滚筒2006和两侧3508发射
pid_type_def pid_3805_2006_speed[4];	
const fp32 PID_3805_2006_speed[3] ={10,0.5,5};  
int speed_3805_2006[3] ={0};

//中间通道3508
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
	
	
	//气动爪子张开
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);

	//两侧3508和滚筒2006
	for(i=0;i<=3;i++)
	{
	  PID_init(&pid_3805_2006_speed[i],PID_POSITION,PID_3805_2006_speed,16000,2000);  
	}
	
	//中间通道3508
	for(i=0;i<=1;i++)
	{
	  PID_init(&pid_passage_3508_speed[i],PID_POSITION,PID_passage_3508_speed,16000,5000);  
	}
	osDelay(20);
	
}


/***********************获取KEY1按键的值********************************/
#define GPIO_KEY GPIOB					//按键引脚——>PB1
#define GPIO_KEY_PIN GPIO_PIN_1   

uint8_t read_key1;
uint8_t keyflag1=0;

void read_key_pin(void)
{
	read_key1=HAL_GPIO_ReadPin(GPIO_KEY,  GPIO_KEY_PIN);
	if(read_key1==GPIO_PIN_RESET)//低电平，按键未按下
	{
		keyflag1=0;
	}
	if(read_key1==GPIO_PIN_SET)//高电平，按键按下
	{
		keyflag1=1;
	}
}


unsigned char flagC = 5;
unsigned char flagR = 1;
void RollerButton(void)
{
/*************************************滚球入仓****************************************/
	if(Robot_Control.Roller==1){	//转动
		if(flagR ==1){
			speed_3805_2006[0] = 12000;       //正
      passage_3508_speed[0] = -2000;    //正
      passage_3508_speed[1] = -800;}    //正
		else if (flagR ==0){  // 当 flagC 等于 1 或 2 时,反转
			speed_3805_2006[0] = -13000;   //反
      passage_3508_speed[0] = 2000;  //反
      passage_3508_speed[1] = -900;} //正
	}	
	else{//静止
		speed_3805_2006[0]=0;  
		passage_3508_speed[0]=0;  
		passage_3508_speed[1]=-900;
	}
}



void warehousing_control(void)
{
/*************************************左右分球****************************************/	
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
		
		if(flagC==1)//左吐球
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
		
		
		if(flagC==2)//右吐球
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

		if(flagC==0)//复位
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
/*************************************夹球上升****************************************/
	if(Robot_Control.Mode==1)
	{
		if(Robot_Control.PlaceOrNot==1)
			{
				#define Tolerance_1 8192*36*0.2
				if(start_angle_record_can2[4]!=0&&start_angle_record_can2[5]!=0&&start_angle_record_can2[6]!=0&&start_angle_record_can2[7]!=0)
					{
						osDelay(1000);
						//抓手夹球
						HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);
						osDelay(200);
						//抓手反转
						angle_gm3508[6] =8192*36*0.42;      				
						angle_gm3508[7] =-8192*36*0.42;
						if((Cumulative_angle_can2[6]>=8192*36*0.42-Tolerance_1&&Cumulative_angle_can2[6]<=8192*36*0.42+Tolerance_1)&&(Cumulative_angle_can2[7]>=-8192*36*0.42-Tolerance_1&&Cumulative_angle_can2[7]<=-8192*36*0.42+Tolerance_1))
							{
								angle_gm3508[4] =8192*19.2*2;
								angle_gm3508[5] =-8192*19.2*2;
							}
					}		
			}
/*************************************放框且复位****************************************/			
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
///*************************************放框且复位****************************************/	
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
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,value1);  //左侧舵机初始值2400  S
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,value2);   //右侧舵机初始值500  T
}

void xiqiu_duoji_set(int16_t value3,int16_t value4)
{
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,value3);  //左侧舵机初始值2500  U
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,value4);   //右侧舵机初始值500  V
}
