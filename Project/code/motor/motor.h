#ifndef _MOTOR_H
#define _MOTOR_H

#include "zf_common_typedef.h"
#include "pid.h"

void Motor_Init();	//�����ʼ�����ں�����ģ���ʼ��



//����ʹ��-Ƶ��
//void Motor_Pwm_Init(uint32 frep);
void Motor_Pwm_Init();
void Motor_Stop();	//ɲ��
void Left_Direction(bool direction);	//���������ת
void Right_Direction(bool direction);	//�Ҳ�������ת


#endif