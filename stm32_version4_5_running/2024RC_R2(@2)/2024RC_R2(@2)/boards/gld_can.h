#ifndef GLD_CAN_H
#define GLD_CAN_H
#include "struct_typedef.h"
#include "can.h"//"can.h"这个文件一定包含，不然找不到CAN_HandleTypeDef。

typedef struct
{
    uint16_t ecd;
    int16_t speed_rpm;
    int16_t given_current;
    uint8_t temperate;
    int16_t last_ecd;
} motor_measure_t;


extern void can_filter_init(void);
extern void CAN_send(CAN_HandleTypeDef hcanx,int16_t SSID,int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);

extern const motor_measure_t *get_motor_message_can1(uint8_t i);
extern const motor_measure_t *get_motor_message_can2(uint8_t i);

extern long int Cumulative_angle_can1[8];
extern int16_t Cumulative_angle_start_flag_can1[8];
extern int16_t start_angle_flag_can1;
extern int16_t start_angle_record_can1[8];

extern long int Cumulative_angle_can2[8];
extern int16_t Cumulative_angle_start_flag_can2[8];
extern int16_t start_angle_flag_can2;
extern int16_t start_angle_record_can2[8];

extern void angle_total_can1(uint8_t i);
extern void angle_total_can2(uint8_t i);

#endif
