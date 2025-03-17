#include "dht11.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"





//void DS18B20_UserConfiduer(void){
//	
//	gpio_init(E4, GPO, GPIO_LOW, GPO_PUSH_PULL);
//	DS18B20_High;
//}


//void DS18B20_Write_Out_Input(unsigned char cmd){
//	
//	if(cmd) // 1 out 0 int
//		gpio_init(E4, GPO, GPIO_LOW, GPO_PUSH_PULL);

//	else
//		gpio_init(E4, GPI, GPIO_LOW, GPI_PULL_UP);
//	
//}

//unsigned char DS18B20_Write_Reset(void){
//	
//	unsigned char dat;
//	
//	DS18B20_Write_Out_Input(1);
//	DS18B20_Low;
//	delay_us(480); // 480us
//	DS18B20_High;
//	delay_us(60); // 480us
//	DS18B20_Write_Out_Input(0);
//	dat = gpio_get_level(E4); // 0
//	delay_us(420); // 480us
//	
//	return dat;
//}
//void DS18B20_Write_Byte(unsigned char cmd){
//	
//	for(unsigned char i=0;i<8;i++){
//			
//		DS18B20_Write_Out_Input(1);
//		DS18B20_Low;
//		delay_us(2); //2us
//		if(cmd&0x01) DS18B20_High;
//		else DS18B20_Low;
//		delay_us(60); //60us
//		DS18B20_High;
//		
//		cmd >>= 1;
//	}
//}
//unsigned char DS18B20_Read_Byte(void){
//	
//	unsigned char dat = 0;
//	
//	for(unsigned char i=0;i<8;i++){
//		
//		dat >>= 1;
//		
//		DS18B20_Write_Out_Input(1);
//		DS18B20_Low;
//		delay_us(2); //2us
//		DS18B20_High;
//		DS18B20_Write_Out_Input(0);
//		if(gpio_get_level(E4) == SET){
//			
//			dat |= 0x80; 
//		}
//		delay_us(60); //60us
//	}
//	return dat;
//}


//float DS18B20_Read_Temp(void){
//	
//	unsigned char MSB=0,MSL=0; unsigned int Temp=0; float Ftemp=0;
//	
//	if(DS18B20_Write_Reset() == RESET){
//		
//		DS18B20_Write_Reset();
//		DS18B20_Write_Byte(0XCC);
//		DS18B20_Write_Byte(0X44);
//		delay_ms(750);//750ms
//		DS18B20_Write_Reset();
//		DS18B20_Write_Byte(0XCC);
//		DS18B20_Write_Byte(0XBE);
//		
//		MSL = DS18B20_Read_Byte();
//		MSB = DS18B20_Read_Byte();
//		Temp = MSB;
//		Temp = Temp << 8|MSL;
//		
//		if((Temp&0XF800) == 0XF800){ // 1111 1000 0000 0000
//			
//			Temp =(((~Temp) + 0X01) * -0.0625);
//		}
//		else{
//			
//			Ftemp = Temp * 0.0625;
//		}
//	}
//	else{
//		
//		printf("DS18B20 NO\r\n");
//		delay_ms(500);
//	}
//	
//	return Ftemp;
//}
























#if 1
//带参宏，可以像内联函数一样使用,输出高电平或低电平
//#define DHT11_DATA_OUT(a)	gpio_set_level(E4,a)
	
 //读取引脚的电平
//#define DHT11_DATA_IN()	gpio_get_level(E4)




///*
// * 函数名：DHT11_Mode_IPU
// * 描述  ：使DHT11-DATA引脚变为上拉输入模式
// * 输入  ：无
// * 输出  ：无
// */
//static void DHT11_Mode_IPU(void)
//{
// 	  GPIO_Init_Type GPIO_InitStructure;

//	  	/*选择要控制的DHT11_PORT引脚*/	
//	  GPIO_InitStructure.Pins = DHT11_PIN;

//	   /*设置引脚模式为浮空输入模式*/ 
//	  GPIO_InitStructure.PinMode = GPIO_PinMode_In_Floating ; 

//	  /*调用库函数，初始化DHT11_PORT*/
//	  GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 
//}

///*
// * 函数名：DHT11_Mode_Out_PP
// * 描述  ：使DHT11-DATA引脚变为推挽输出模式
// * 输入  ：无
// * 输出  ：无
// */
//static void DHT11_Mode_Out_PP(void)
//{
// 	GPIO_Init_Type GPIO_InitStructure;

//	 	/*选择要控制的DHT11_PORT引脚*/															   
//  	GPIO_InitStructure.Pins = DHT11_PIN;	

//	/*设置引脚模式为通用推挽输出*/
//  	GPIO_InitStructure.PinMode = GPIO_PinMode_Out_PushPull;   

//	/*设置引脚速率为50MHz */   
//  	GPIO_InitStructure.Speed = GPIO_Speed_50MHz;

//	/*调用库函数，初始化DHT11_PORT*/
//  	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 	 
//}



unsigned char Time = 0;


//void delay_us(int dly){
//	delay_us(dly);

//}


void DHT_Mode(unsigned char mode){
	
	
	if(mode){ // 1 out 0 int
		gpio_init(E4, GPO, GPIO_LOW, GPO_PUSH_PULL);
	}
	else{
		
		gpio_init(E4, GPI, GPIO_LOW, GPI_PULL_UP);
	}
}


void DHT_Sends_Start(void){
	
	DHT_Mode(OUT);
	
	DHT_Low;
	delay_ms(18);//18ms
	DHT_High;
	delay_us(40);//40us
}

void DHT_Sends_Response(void){
	
	DHT_Mode(INT);
	
	while((gpio_get_level(E4) == 0) && (Time < 100)){ //low 80us
		
		Time++;
		delay_us(1);//100us DHT=0 80us;
	}
	Time = 0;
	
	while((gpio_get_level(E4) == 1) && (Time < 100)){ //high 80us
		
		Time++;
		delay_us(1);//100us DHT=0 80us;
	}
	Time = 0;
}
unsigned char DHT11_Read_Byte(void){
	
	unsigned char data = 0;
	
	for(unsigned char i=0;i<8;i++){
		
		DHT_Mode(INT);
		
		while((gpio_get_level(E4) == 0) && (Time < 100)){ //high 50us // 1 - 0
		
			Time++;
			delay_us(1);//100us DHT=0 80us;
		}
		Time = 0;
		
		data <<= 1;
		
		delay_us(40);//get high 70us
		
		if(gpio_get_level(E4) == 1){
			
			data |= 0x01;
			
			while((gpio_get_level(E4) == 1) && (Time < 100)){ //high 70us
		
				Time++;
				delay_us(1);//100us DHT=0 80us;
			}
			Time = 0;
		}
	}
	return data;
}
void DHT11_Read_Data(int *temp,int *humi){
	
	unsigned char DATA[5]={0,0,0,0,0};
	
	DHT_Sends_Start();
	DHT_Sends_Response();
	
	for(unsigned char i=0;i<5;i++){
		
		DATA[i] = DHT11_Read_Byte();
	}
	delay_ms(1);//1ms 50us
	
	if((DATA[0]+DATA[1]+DATA[2]+DATA[3]) == DATA[4]){
		
		*humi = DATA[0]+DATA[1]/100.0;
		*temp = DATA[2]+DATA[3]/100.0;
	}
	else{
			*humi = 55;
			*temp = 25;
//		for(unsigned char i=0;i<5;i++){
//			
//			DATA[i] = 0;
//		}
	}
}
#endif