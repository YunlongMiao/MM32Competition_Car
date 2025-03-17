#include "zf_driver_adc.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "ADC_USE.h"

void ADC_Use_Init(){
	
	//声音
	adc_init(ADC1_CH10_C0, ADC_12BIT);
	
	
	//CO
	adc_init(ADC1_CH12_C2, ADC_12BIT);

	//PM2.5
  adc_init(ADC1_CH13_C3, ADC_12BIT);									 //PM2.5,用ADC2-c3
	gpio_init(B1, GPO, GPIO_HIGH, GPO_PUSH_PULL);
	
		//电压
	adc_init(ADC2_CH14_C4, ADC_12BIT);                 //电池检测,用ADC2-C4
}

float ADC_POWER(){
	
	int i = 0;
	uint16_t voltage_adc = 0;
	
	for(i=0; i<5; i++)
		voltage_adc += adc_convert(ADC2_CH14_C4);
	voltage_adc /= 5;
	
	return 13.2 * voltage_adc / 4096; // 根据逐飞科技学习主板分压计算 测得应该是电池电压 1/4 那么最大量程 13.2V
	
}



float ADC_Sound(){
	int i = 0;
	uint16_t voltage_adc = 0;
	
	for(i=0; i<5; i++)
		voltage_adc += adc_convert(ADC1_CH10_C0);
	voltage_adc /= 5;
	return 200 * 5.0 * voltage_adc / 4096; // 根据逐飞科技学习主板分压计算 测得应该是电池电压 1/4 那么最大量程 13.2V
	
}



//float ADC_Tem(){
//	int i = 0;
//	uint16_t voltage_adc = 0;
//	
//	for(i=0; i<5; i++)
//		voltage_adc += adc_convert(ADC1_CH11_C1);
//	voltage_adc /= 5;

//	return 5.0 * voltage_adc / 4096; // 根据逐飞科技学习主板分压计算 测得应该是电池电压 1/4 那么最大量程 13.2V
//	
//}



float ADC_Co(){
	
	int i = 0;
	uint16_t voltage_adc = 0;
	
	for(i=0; i<5; i++)
		voltage_adc += adc_convert(ADC1_CH12_C2);
	voltage_adc /= 5;
	
	return 10 * 3.3 * voltage_adc / 4096; // 根据逐飞科技学习主板分压计算 测得应该是电池电压 1/4 那么最大量程 13.2V
	
}



float ADC_PM25_Design(){
	int i = 0;
	uint16_t pm25_adc = 0;
	for(i=0; i<10; i++){
		gpio_set_level(B1,1);
		delay_us(280);
		pm25_adc = adc_convert(ADC2_CH8_B0);
		delay_us(40);
		gpio_set_level(B1,0);
		delay_us(9680);
	}
	pm25_adc /= 10;
	return 2 * pm25_adc / 4096.f * 3.3f;
	 
}

float ADC_PM25(){

	float pm25_power = 0;

	pm25_power = ADC_PM25_Design();
  pm25_power = (0.17*pm25_power-0.1)*1000;  //乘以1000单位换成ug/m3//
	if(pm25_power>=0)
		return pm25_power;
	else
		return 0-pm25_power;
	return 265;
}