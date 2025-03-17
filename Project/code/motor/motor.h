#ifndef _MOTOR_H
#define _MOTOR_H

#include "zf_common_typedef.h"
#include "pid.h"

void Motor_Init();	//电机初始化，内含各个模块初始化



//测试使用-频率
//void Motor_Pwm_Init(uint32 frep);
void Motor_Pwm_Init();
void Motor_Stop();	//刹车
void Left_Direction(bool direction);	//左侧电机正反转
void Right_Direction(bool direction);	//右侧电机正反转


#endif