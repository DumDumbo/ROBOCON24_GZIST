#ifndef CHASSIS_TASK_H
#define CHASSIS_TASK_H
#include "main.h"
#include "gpio.h"
#include "tim.h"


#include "pid.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"

extern float actual_speed[3];
extern int map(int x, int in_min, int in_max, int out_min, int out_max);
extern int i;
#endif
