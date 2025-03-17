#include "sensing_control.h"
#include "zf_driver_delay.h"
#include "ADC_USE.h"
#include "dht11.h"
#include "zf_driver_gpio.h"



void Sensing_Control_Init()
{
	ADC_Use_Init();	//ADC����
	gpio_init(E9, GPO, GPIO_LOW, GPO_PUSH_PULL);	//������
	gpio_init(B0, GPI, GPIO_LOW, GPI_PULL_UP);		//����
}


void Get_All_Sensing(Control_Data_TypeDef *Control_Data)
{
	Control_Data->power =  ADC_POWER();	//�����ѹ��ȡ
	delay_ms(10);
	Control_Data->pm2_5 = 	ADC_PM25();		//��Χ����PM2.5��ֵ��ȡ��ug/m3��
	delay_ms(10);
	Control_Data->Sound =	ADC_Sound();		//����
	delay_ms(10);
	Control_Data->Co    =	ADC_Co();				//CO
	delay_ms(10);
	DHT11_Read_Data(&Control_Data->Tem,&Control_Data->ShiDu);
	delay_ms(10);
	Control_Data->fire = gpio_get_level(B0);
	
}