#ifndef _PID_H
#define _PID_H

#include "zf_common_typedef.h"



float Gray_PID_value(float error);								 //�Ҷ�
int velocity_PID_value_L(int velocity);              //�ٶȻ�
int velocity_PID_value_R(int velocity);              //�ٶȻ�
void Error_xianfu(int max);                        //�Ҷ�����޷�
void Velocity_xianfu(int max);										 //�ٶ��޷�

#endif