#ifndef _PID_H
#define _PID_H

#include "zf_common_typedef.h"



float Gray_PID_value(float error);								 //灰度
int velocity_PID_value_L(int velocity);              //速度环
int velocity_PID_value_R(int velocity);              //速度环
void Error_xianfu(int max);                        //灰度误差限幅
void Velocity_xianfu(int max);										 //速度限幅

#endif