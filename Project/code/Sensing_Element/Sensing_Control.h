#ifndef _SENSING_CONTROL_H
#define _SENSING_CONTROL_H

#include "zf_common_typedef.h"



typedef struct
{
	int  power;		//电压
	int  pm2_5;	 	//PM2.5
	int  Tem;	 		//温度
	int  Sound;	 	//声音
	int  Co;	 		//co
	int  ShiDu;
	int   fire;
}Control_Data_TypeDef;




void Sensing_Control_Init();

void Get_All_Sensing(Control_Data_TypeDef *Control_Data);


#endif



#if 0

#include "zf_common_headfile.h"
#include "ADC_USE.h"
#include "motor_control.h"
#include "Sensing_Control.h"

#define PIT_Motor                         (TIM7_PIT ) // 使用的周期中断编号 如果修改 需要同步对应修改周期中断编号与 isr.c 中的调用


int main(){
	ADC_Data_TypeDef ADC_Data;
	
  clock_init(SYSTEM_CLOCK_120M);                                              // 初始化芯片时钟 工作频率为 120MHz
  debug_init();
	Sensing_Control_Init();
	gpio_init(H2, GPO, GPIO_LOW, GPO_PUSH_PULL);
	delay_ms(1000);
	while(1){
		

		Get_All_Sensing(&ADC_Data);
		
		printf("ADC_power=%f\r\n",ADC_Data.power);
		printf("ADC_PM2_5=%f\r\n",ADC_Data.pm2_5);
		printf("ADC_PM2_5=%f\r\n",ADC_Data.Tem);
		printf("ADC_PM2_5=%f\r\n",ADC_Data.Sound);
		printf("ADC_PM2_5=%f\r\n",ADC_Data.Co);
		
		delay_ms(1500);

	}
}

void Motor_pit_handler (void)
{

}


#endif