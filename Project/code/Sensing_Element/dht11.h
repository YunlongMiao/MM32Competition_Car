#ifndef __DHT11_H
#define	__DHT11_H

#include "zf_common_typedef.h" 


#define SET 1
#define RESET 0

#define HIGH  1
#define LOW   0

#define DS18B20_High gpio_set_level(E4,1)
#define DS18B20_Low gpio_set_level(E4,0)


float DS18B20_Read_Temp(void);
void DS18B20_UserConfiduer(void);



#if 1

#define OUT 1
#define INT 0

#define HIGH  1
#define LOW   0

#define DHT_Low gpio_set_level(E4,0)
#define DHT_High gpio_set_level(E4,1)


#define DHT11_PIN     	GPIO_PIN_4
#define DHT11_PORT      GPIOE


typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
		                 
}DHT11_Data_TypeDef;




//void DHT11_GPIO_Config(void);
//static void DHT11_Mode_IPU(void);
//static void DHT11_Mode_Out_PP(void);
//uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
//static uint8_t Read_Byte(void);

void DHT11_Read_Data(int *temp,int *humi);

#endif /* __DHT11_H */

#endif





