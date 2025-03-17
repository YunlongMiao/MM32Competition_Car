#include "sensing_control.h"
#include "zf_driver_delay.h"
#include "ADC_USE.h"
#include "dht11.h"
#include "zf_driver_gpio.h"



void Sensing_Control_Init()
{
	ADC_Use_Init();	//ADC部分
	gpio_init(E9, GPO, GPIO_LOW, GPO_PUSH_PULL);	//蜂鸣器
	gpio_init(B0, GPI, GPIO_LOW, GPI_PULL_UP);		//火焰
}


void Get_All_Sensing(Control_Data_TypeDef *Control_Data)
{
	Control_Data->power =  ADC_POWER();	//主板电压获取
	delay_ms(10);
	Control_Data->pm2_5 = 	ADC_PM25();		//周围环境PM2.5数值获取（ug/m3）
	delay_ms(10);
	Control_Data->Sound =	ADC_Sound();		//声音
	delay_ms(10);
	Control_Data->Co    =	ADC_Co();				//CO
	delay_ms(10);
	DHT11_Read_Data(&Control_Data->Tem,&Control_Data->ShiDu);
	delay_ms(10);
	Control_Data->fire = gpio_get_level(B0);
	
}