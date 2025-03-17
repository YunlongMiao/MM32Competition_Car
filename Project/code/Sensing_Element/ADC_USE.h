#ifndef _ADC_USE_H
#define _ADC_USE_H

void ADC_Use_Init();

float ADC_POWER();	//主板电压获取
float ADC_PM25();		//周围环境PM2.5数值获取（ug/m3）
float ADC_Tem();
float ADC_Sound();
float ADC_Co();
#endif