#ifndef UPPER_TASK_H
#define UPPER_TASK_H

#include "main.h"
#include "gpio.h"
#include "tim.h"

#include "gld_can.h"
#include "pid.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"


extern pid_type_def pid_3805_2006_speed[4];
extern pid_type_def pid_passage_3508_speed[2];
extern pid_type_def motor_pid_3508_pos[4];
extern pid_type_def motor_pid_3508_v[4];

extern void tuqiu_duoji_set(int16_t value1,int16_t value2);
extern void xiqiu_duoji_set(int16_t value3,int16_t value4);

extern int speed_3805_2006[3];
extern int passage_3508_speed[2];
extern float angle_gm3508[8];

extern uint8_t keyflag1;

#endif
