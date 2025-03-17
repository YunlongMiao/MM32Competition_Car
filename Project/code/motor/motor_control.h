#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H
#include "zf_common_typedef.h"
#include "zf_driver_pwm.h"

void Motor_Control_Init();
//void Gray_Transition();

int Gray_Judge();
uint8 Num_Exchange_4(uint8 num);
void Gray_Control();

void SETPWM(int PWM,pwm_channel_enum PIN);
void PWM_Xianfu(int max,int *PWM);		//PWMÏÞ·ù
int Read_Encoder1(void);							//¶ÁÈ¡±àÂëÆ÷
int Read_Encoder2(void);

#endif








#if 0

void Gray_Transition(){

	uint8 temp = 0,i = 0;
	temp = gw_gray_serial_read();
	for(i=0; i<8; i++){
		if(temp & 0x80)
			Gray_Num[7-i] = 1;
		else
			Gray_Num[7-i] = 0;
		temp = temp << 1;
//		printf("\r\nGray_Num[%d]=%d",7-i,Gray_Num[7-i]);
	}
}
#endif
