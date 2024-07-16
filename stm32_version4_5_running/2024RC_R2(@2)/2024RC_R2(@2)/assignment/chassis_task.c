/**
* Function       
* @author        YH
* @date          2023.01.23
* @brief         FreeRTOS
* @retval        void
*/

#include "chassis_task.h"
#include "message_task.h"
#include "upper_task.h"
#include "gld_can.h"
#include "struct_typedef.h"
#include <math.h>

const motor_measure_t *motor_data[8];//电机结构体指针
const motor_measure_t *motor_data_can2[8];

/*3508电机底盘**********************************************/

//速度环
pid_type_def motor_pid[4];	
const fp32 PID[3] ={20,0.5,5};      

//imu去漂
pid_type_def gyro_pid;
const fp32 PID_gyro[3] ={20,0.01,0.5};

//里程计
pid_type_def chassis_odometer[3]; 
const fp32 PID_odometer[3] ={2.5,0,0.5};

/*升降爪手*/
pid_type_def motor_pid_3508_pos[4];
pid_type_def motor_pid_3508_v[4];
fp32 PID_3508_pos[3] ={0.5,0.001,20};//10,0.05,1.2
fp32 PID_3508_v[3] ={1,0,1.1};//3,0,0.5
float angle_gm3508[8]={0};

//全向轮运动解析
float w_gyro =0;
float gyro_set =0;
int16_t set_speed[5] = {0,0,0,0,0};
float wheel_one,wheel_two,wheel_three,wheel_four;
float wheel[4] ={0};
int timee =0;

float line_speed[4] ={0};
float actual_speed[3] ={0};
float xyz_displacement[3] ={0};

void chassis_pid(void);
void chassis_movement(short vx,short vy,short w);

void chassis_odometer_movement(short wheel_x,short wheel_y,short wheel_w);
void odometer_xyz(short odometer_x,short odometer_y,short odometer_w);
/***************************************************************/

//初始化
int i=0;
int flag =0;
int control =1;
void chassis_init(void);
void remote_control(void);
int map(int x, int in_min, int in_max, int out_min, int out_max);              
void warehousing_control(void);

int actual_distance_xyz[3] ={0}; 

void chassis_task(void const * argument)
{
	chassis_init();
	while(1)
	{	
		remote_control();
		if(control ==2)
		{
			xiqiu_duoji_set(2500,500);
			
			set_speed[0]=Robot_Control.X_speed;
			set_speed[1]=-Robot_Control.Y_speed;
			set_speed[2]=Robot_Control.Z_speed;
			chassis_movement(set_speed[0],set_speed[1],set_speed[2]);
		}

		else
		{
			CAN_send(hcan1,0x200,0,0,0,0);
			CAN_send(hcan1,0x1FF,0,0,0,0);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_SET);
			HAL_Delay(100);//延时	
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);
			HAL_Delay(80);//延时	
		}	
	}
	
}


void chassis_init(void)
{
	/*获取can1电机数据*/
	for(i = 0;i<=7;i++)
	{
		motor_data[i] = get_motor_message_can1(i); 		           
	}
	/*获取can2电机数据*/
	for(i = 0;i<=7;i++)
	{
		motor_data_can2[i] = get_motor_message_can2(i); 		           
	}
	
	//陀螺仪
	PID_init(&gyro_pid,PID_POSITION,PID_gyro,3000,500);
	
	//里程计
	for(i=0;i<=2;i++)
	{
		PID_init(&chassis_odometer[i],PID_POSITION,PID_odometer,500,50);
	}
	//底盘PID初始化
	for(i=0;i<=3;i++)
	{
		PID_init(&motor_pid[i],PID_POSITION,PID,16000,2000);  
	}

	//GM3508升降
	for(i=0;i<=1;i++)
	{
		PID_init(&motor_pid_3508_pos[i],PID_POSITION,PID_3508_pos,8192,200);
		PID_init(&motor_pid_3508_v[i],PID_POSITION,PID_3508_v,5000,500);  
	}
	
	//GM2006抓手
	for(i=2;i<=3;i++)
	{
		PID_init(&motor_pid_3508_pos[i],PID_POSITION,PID_3508_pos,5000,200); 
		PID_init(&motor_pid_3508_v[i],PID_POSITION,PID_3508_v,8000,500);  
	}
	
	osDelay(20);	
}

int map(int x, int in_min, int in_max, int out_min, int out_max)               //映射函数
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	
}

void chassis_pid(void)
{
	set_speed[0]=map(RC_Ctl.rc.ch3,364,1684,-2000,2000);
	set_speed[1]=map(RC_Ctl.rc.ch2,364,1684,-2000,2000);
	set_speed[2]=map(RC_Ctl.rc.ch0,364,1684,-3150,3150);
	
	if(flag ==0)
	{
		w_gyro = 0;
		if(RC_Ctl.rc.s1 ==2)
		{
			gyro_set = map(yaw_angle,0,360,-180,180);
			flag = 1;
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);
		}	
	}

	
	if(flag ==1)
	{
		w_gyro = gyro_pid.out;	
	}
	
//	if(RC_Ctl.rc.ch2 ==1024&&RC_Ctl.rc.ch3 ==1024)
//    {
//		gyro_set = yaw_angle;;
//    }
	
	chassis_movement(set_speed[0],set_speed[1],set_speed[2]);
	   
}

/*全向轮逆运动解析*/
void chassis_movement(short vx,short vy,short w)
{
	#define car_L 348
	#define SIN45 0.707 
	wheel_one   = -vx*SIN45 -vy*SIN45 + w*car_L*0.001-w_gyro;
	wheel_two   = -vx*SIN45 +vy*SIN45 + w*car_L*0.001-w_gyro;
	wheel_three	= vx*SIN45 +vy*SIN45 + w*car_L*0.001-w_gyro;
	wheel_four	= vx*SIN45 -vy*SIN45 + w*car_L*0.001-w_gyro;
	
}

void odometer_xyz(short odometer_x,short odometer_y,short odometer_w)
{
	actual_distance_xyz[0] =odometer_x;
	actual_distance_xyz[1] =odometer_y;
	actual_distance_xyz[2] =odometer_w;
}

/*里程计运动解析*/
void chassis_odometer_movement(short wheel_x,short wheel_y,short wheel_w)
{
	#define car_L 348
	#define SIN45 0.707 
	wheel[0]   = -wheel_x*SIN45 -wheel_y*SIN45 + wheel_w*car_L*0.001;
	wheel[1]   = -wheel_x*SIN45 +wheel_y*SIN45 + wheel_w*car_L*0.001;
	wheel[2]   =  wheel_x*SIN45 +wheel_y*SIN45 + wheel_w*car_L*0.001;
	wheel[3]   =  wheel_x*SIN45 -wheel_y*SIN45 + wheel_w*car_L*0.001;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM6)//2ms
	{
/*****************************************************CAN1*************************************************************/
		#define rpm_c_v  (2*3.14*0.052*0.017*63.5)//2Π*1/减速比*1/60*轮子半径（单位mm）
		#define arcsin45  1.414f 
		line_speed[0] =(motor_data[0]->speed_rpm)*rpm_c_v;
		line_speed[1] =(motor_data[1]->speed_rpm)*rpm_c_v;
		line_speed[2] =(motor_data[2]->speed_rpm)*rpm_c_v;
		line_speed[3] =(motor_data[3]->speed_rpm)*rpm_c_v;
		
		/*全向轮正运动解析，x和y单位为mm/s，w的单位为rad/s*/
		actual_speed[0] = (-line_speed[0]-line_speed[1]+line_speed[2]+line_speed[3])*arcsin45*0.25f;    //y
		actual_speed[1] = (-line_speed[0]+line_speed[1]+line_speed[2]-line_speed[3])*arcsin45*0.25f;   //x
		actual_speed[2] = (line_speed[0]+line_speed[1]+line_speed[2]+line_speed[3])*0.25f*0.0029f*1000;//w
		
		if(flag ==1)
		{
			PID_calc(1,&gyro_pid,yaw_angle,gyro_set);
		}
		//底盘
		PID_calc(0,&motor_pid[0],line_speed[0],wheel_one+wheel[0]);			             
		PID_calc(0,&motor_pid[1],line_speed[1],wheel_two+wheel[1]);
		PID_calc(0,&motor_pid[2],line_speed[2],wheel_three+wheel[2]);
		PID_calc(0,&motor_pid[3],line_speed[3],wheel_four+wheel[3]);

		
		//滚筒2006和两侧3508发射
		for(i=0;i<=2;i++)
		{
			PID_calc(0,&pid_3805_2006_speed[i], motor_data[4+i]->speed_rpm, speed_3805_2006[i]);
		}

		//中间通道3508
		for(i=0;i<=2;i++)
		{
			PID_calc(0,&pid_passage_3508_speed[i], motor_data_can2[i]->speed_rpm, passage_3508_speed[i]);
		}		
		//激光测距
//		PID_calc(0,&chassis_odometer[0],data_10_usatr8,actual_distance_xyz[0]);
//		PID_calc(0,&chassis_odometer[1],xyz_displacement[1],actual_distance_xyz[1]);
//		chassis_odometer_movement(chassis_odometer[0].out,chassis_odometer[1].out,0);
				
		//升降&抓手
		for(i=0;i<=3;i++)
		{
			PID_calc(0,&motor_pid_3508_pos[i], Cumulative_angle_can2[4+i], angle_gm3508[4+i]);
			PID_calc(0,&motor_pid_3508_v[i], motor_data_can2[4+i]->speed_rpm, motor_pid_3508_pos[i].out);  
		}
		
		CAN_send(hcan1,0x200,motor_pid[0].out,motor_pid[1].out,motor_pid[2].out,motor_pid[3].out);
		CAN_send(hcan1,0x1FF,pid_3805_2006_speed[0].out,pid_3805_2006_speed[1].out,pid_3805_2006_speed[2].out,0);

		CAN_send(hcan2,0x200,pid_passage_3508_speed[0].out,pid_passage_3508_speed[1].out,0,0);	
		CAN_send(hcan2,0x1FF,motor_pid_3508_v[0].out,motor_pid_3508_v[1].out,motor_pid_3508_v[2].out,motor_pid_3508_v[3].out);
  }

	if(htim->Instance==TIM7)//0.1s
	{
//		xyz_displacement[0] += actual_speed[0]*0.1;
//		xyz_displacement[1] += actual_speed[1]*0.1;
//		timee +=1;
//		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_14);
	}	
 
}
void remote_control(void)
{
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)==1)
	{
		control =2;
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);
	}

	if(364<=RC_Ctl.rc.ch2&&RC_Ctl.rc.ch2<1024)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET);
	}
	
	if(1024<RC_Ctl.rc.ch2&&RC_Ctl.rc.ch2<=1684)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET);
	}
	
	if(364<=RC_Ctl.rc.ch3&&RC_Ctl.rc.ch3<1024)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET);
	}
	
	if(1024<RC_Ctl.rc.ch3&&RC_Ctl.rc.ch3<=1684)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_RESET);
	}	
	
	if(364<=RC_Ctl.rc.ch0&&RC_Ctl.rc.ch0<1024)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET);
	}	
	
	if(1024<RC_Ctl.rc.ch0&&RC_Ctl.rc.ch0<=1684)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
	}	
	
	if(364<=RC_Ctl.rc.ch1&&RC_Ctl.rc.ch1<1024)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
	}	
	
	if(1024<RC_Ctl.rc.ch1&&RC_Ctl.rc.ch1<=1684)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_RESET);
	}
	
	if(RC_Ctl.rc.ch2 ==1024)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET);
	}
	
	if(RC_Ctl.rc.ch3 ==1024)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_SET);
	}
	
	if(RC_Ctl.rc.ch0 ==1024)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
	}
	
	if(RC_Ctl.rc.ch1 ==1024)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_SET);
	}

}
