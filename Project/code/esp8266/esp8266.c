#include "esp8266.h"
#include "zf_device_wifi_uart.h"
#include "zf_driver_uart.h"
#include "sensing_control.h"
#include "zf_common_debug.h"

//void ESP_Init(){

//	 uart_init(WIFI_UART_INDEX, 115200, WIFI_UART_RX_PIN, WIFI_UART_TX_PIN);     // 初始化WiFi模块所使用的串口
//   uart_rx_interrupt(WIFI_UART_INDEX, 1);
//	
//}


void Get_Sensing()
{
	float num[9] = {0xa0,0xa0,};
	Control_Data_TypeDef Control_Data;
	Get_All_Sensing(&Control_Data);
//	num[2] = Control_Data.power;
//	num[3] = Control_Data.pm2_5;
//	num[4] = Control_Data.Tem;
//	num[5] = Control_Data.Sound;
//	num[6] = Control_Data.Co;
//	num[7] = Control_Data.ShiDu;
//	num[8] = Control_Data.fire;
	
//	uart_write_buffer(UART_6,num,sizeof(num));
//	uart_tx_interrupt(UART_6,1);
//	printf("%d ",0xa0);
//	printf("%d ",0xa0);
//	printf("%.2f ",Control_Data.power);
//	printf("%.2f ",Control_Data.pm2_5);
//	printf("%.2f ",Control_Data.Tem);
//	printf("%.2f ",Control_Data.Sound);
//	printf("%.2f ",Control_Data.Co);
//	printf("%.2f ",Control_Data.ShiDu);
//	printf("%d ",Control_Data.fire);
	printf("%.2f,%.2f,%.2f,%.2f,%d",Control_Data.power,Control_Data.pm2_5,Control_Data.Tem,Control_Data.ShiDu,Control_Data.fire);

}






























//#include "zf_common_headfile.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

///*
//*************************************
//宏定义
//*************************************
//*/
//#define WIFI_SSID_TEST          "vivoS7t"
//#define WIFI_PASSWORD_TEST      "qwertyuiopp"

//#define MQTT_CLIENT_ID   "k011hYO0ERp.ESP8266|securemode=2\,signmethod=hmacsha256\,timestamp=1690170780892|"   
//#define MQTT_USER_NAME   "ESP8266&k011hYO0ERp"
//#define MQTT_PASSWD      "7936f2860e74d03d2e11fb1105a00373901d006a525d35787a1a9ca9edace847"
//#define BROKER_ASDDRESS  "iot-06z00c1xbz865fl.mqtt.iothub.aliyuncs.com"
//#define SUB_TOPIC        "/sys/k011hYO0ERp/ESP8266/thing/service/property/set"
//#define PUB_TOPIC        "/sys/k011hYO0ERp/ESP8266/thing/event/property/post"
//#define JSON_FORMAT      "{\\\"params\\\":{\\\"voltage\\\":%f\\,\\\"AQI\\\":%d\\,\\\"Humidity\\\":%f\\,\\\"temperature\\\":%f\\}\\,\\\"version\\\":\\\"1.0.0\\\"}"


//static u8 Check(void);
//static u8 Init(u8 *prx,u16 rxlen,u8 *ptx,u16 txlen);
//static void Restore(void);
//static u8 ConnectAP(char* ssid,char* pswd);
//static u8 ConnectServer(char* mode,char* ip,u16 port);
//static u8 DisconnectServer(void);
//static u8 OpenTransmission(void);
//static void CloseTransmission(void);
//static void SendString(char* str);
//static void SendBuf(u8* buf,u16 len);


//_typdef_net _net=
//{
//	0,0,
//	0,0,
//	Check,
//	Init,
//	Restore,
//	ConnectAP,
//	ConnectServer,
//	DisconnectServer,
//	OpenTransmission,
//	CloseTransmission,
//	SendString,
//	SendBuf
//};






////void esp8266_init(void){
////		uint8 buffer[] = (uint8_t *)"AT+MQTTUSERCFG=0,1,\""MQTT_CLIENT_ID"\",\""MQTT_USER_NAME"\",\""MQTT_PASSWD"\",0,0,\"\"\r\n"
////	// 此处编写用户代码 例如外设初始化代码等
////    printf("\r\n Wi-Fi UART init.");

////    // 当前使用的是 WIFI 串口模块的 station 模式 可以用于连接路由器 WIFI
////    // 
////    // 发送数据方式可以使用命令发送(默认) 也可以使用透传发送 可以在 wifi_uart_init 函数内修改 <当模块作为服务器时 只能使用命令方式发送数据>
////    while(wifi_uart_init(WIFI_SSID_TEST, WIFI_PASSWORD_TEST, WIFI_UART_STATION))	//串口模式初始化
////    {
////        system_delay_ms(500);                                                   // 初始化失败 等待 500ms
////    }
////		
////		printf("\r\n module version:%s",wifi_uart_information.wifi_uart_version);   // 模块固件版本
////    printf("\r\n module mac    :%s",wifi_uart_information.wifi_uart_mac);       // 模块 MAC 信息
////    printf("\r\n module ip     :%s",wifi_uart_information.wifi_uart_local_ip);  // 模块 IP 地址
////    printf("\r\n module port   :%s",wifi_uart_information.wifi_uart_local_port);// 模块 PORT 信息
////		
////		
////	printf("6.MQTT USER CONFIG\r\n");
////	while(wifi_uart_send_buffer(,
////                          strlen("AT+MQTTUSERCFG=0,1,\""MQTT_CLIENT_ID"\",\""MQTT_USER_NAME"\",\""MQTT_PASSWD"\",0,0,\"\"\r\n"),"OK")!=0)
////	{
////		system_delay_ms(2000);
////	}
//////	
//////	wifi_uart_read_buffer (&buffer,  sizeof(buffer));
////		
////}


///**
// * 功能：恢复出厂设置
// * 参数：None
// * 返回值：None
// * 说明:此时ESP8266中的用户设置将全部丢失回复成出厂状态
// */
//static void Restore(void)
//{
//	_net.CloseTransmission();           //退出透传
//    delay_ms(500);
//	_net.SendString("AT+RESTORE\r\n");//恢复出厂 	
////    NVIC_SystemReset();                 //同时重启单片机   
//}


///**
// * 功能：检查ESP8266是否正常
// * 参数：None
// * 返回值：ESP8266返回状态
// *        非0 ESP8266正常
// *        0 ESP8266有问题  
// */
//static unsigned char Check(void)
//{
//	unsigned char check_cnt=5;
//	while(check_cnt--)
//	{
//		memset(_net.rxbuf,0,_net.rxlen); 	 //清空接收缓冲
//		_net.SendString("AT\r\n");     		 //发送AT握手指令	
//		if(FindStr((char*)_net.rxbuf,"OK",200) != 0)
//		{
//			return 1;
//		}
//	}
//	return 0;
//}





///**
// * 功能：连接热点
// * 参数：
// *         ssid:热点名
// *         pwd:热点密码
// * 返回值：
// *         连接结果,非0连接成功,0连接失败
// * 说明： 
// *         失败的原因有以下几种(UART通信和ESP8266正常情况下)
// *         1. WIFI名和密码不正确
// *         2. 路由器连接设备太多,未能给ESP8266分配IP
// */
//static u8 ConnectAP(char* ssid,char* pswd)
//{
//	u8 cnt=5;
//	while(cnt--)
//	{
//		memset(_net.rxbuf,0,_net.rxlen);     
//		_net.SendString("AT+CWMODE_CUR=1\r\n");              //设置为STATION模式	
//		if(FindStr((char*)_net.rxbuf,"OK",200) != 0)
//		{
//			break;
//		}             		
//	}
//	if(cnt == 0) 
//		return 0;

//	cnt=2;
//	while(cnt--)
//	{
//		memset(_net.txbuf,0,_net.txlen);                            //清空发送缓冲
//		memset(_net.rxbuf,0,_net.rxlen);                            //清空接收缓冲
//		sprintf((char*)_net.txbuf,"AT+CWJAP_CUR=\"%s\",\"%s\"\r\n",ssid,pswd);//连接目标AP
//		_net.SendString((char*)_net.txbuf);	
//		if(FindStr((char*)_net.rxbuf,"OK",8000)!=0)                      //连接成功且分配到IP
//		{
//			return 1;
//		}
//	}
//	return 0;
//}





///**
// * 功能：使用指定协议(TCP/UDP)连接到服务器
// * 参数：
// *         mode:协议类型 "TCP","UDP"
// *         ip:目标服务器IP
// *         port:目标是服务器端口号
// * 返回值：
// *         连接结果,非0连接成功,0连接失败
// * 说明： 
// *         失败的原因有以下几种(UART通信和ESP8266正常情况下)
// *         1. 远程服务器IP和端口号有误
// *         2. 未连接AP
// *         3. 服务器端禁止添加(一般不会发生)
// */
//static u8 ConnectServer(char* mode,char* ip,u16 port)
//{
//	u8 cnt;
//   
//    _net.CloseTransmission();                   //多次连接需退出透传
//    delay_ms(500);

//	//连接服务器
//	cnt=2;
//	while(cnt--)
//	{
//		memset(_net.rxbuf,0,_net.rxlen);      
//		memset(_net.txbuf,0,_net.txlen);   
//		sprintf((char*)_net.txbuf,"AT+CIPSTART=\"%s\",\"%s\",%d\r\n",mode,ip,port);
//		_net.SendString((char*)_net.txbuf);
//		if(FindStr((char*)_net.rxbuf,"CONNECT",8000) !=0 )
//		{
//			break;
//		}
//	}
//	if(cnt == 0) 
//		return 0;
//	
//	//设置透传模式
//	if(_net.OpenTransmission()==0) return 0;
//	
//	//开启发送状态
//	cnt=2;
//	while(cnt--)
//	{
//		memset(_net.rxbuf,0,_net.rxlen); 
//		_net.SendString("AT+CIPSEND\r\n");//开始处于透传发送状态
//		if(FindStr((char*)_net.rxbuf,">",200)!=0)
//		{
//			return 1;
//		}
//	}
//	return 0;
//}




///**
// * 功能：主动和服务器断开连接
// * 参数：None
// * 返回值：
// *         连接结果,非0断开成功,0断开失败
// */
//static u8 DisconnectServer(void)
//{
//	u8 cnt;
//    _net.CloseTransmission();	//退出透传
//    delay_ms(500);
//	while(cnt--)
//	{
//		memset(_net.rxbuf,0,_net.rxlen);  
//		_net.SendString("AT+CIPCLOSE\r\n");//关闭链接

//		if(FindStr((char*)_net.rxbuf,"CLOSED",200)!=0)//操作成功,和服务器成功断开
//		{
//			break;
//		}
//	}
//	if(cnt) return 1;
//	return 0;
//}



///**
// * 功能：透传模式下的数据发送函数
// * 参数：
// *      buffer:待发送数据
// * 返回值：None
// */
//static void SendBuf(u8* buf,u16 len)
//{
//    memset(_net.rxbuf,0,_net.rxlen);
//	#ifdef _DEBUG_NET
//	Usart1_SendBuf(buf,len);
//	#endif	
//	Net_SendBuf(buf,len);
//}





///**
// * 功能：透传模式下的数据发送函数
// * 参数：
// *      buffer:待发送数据
// * 返回值：None
// */
//static void SendString(char* str)
//{
//    memset(_net.rxbuf,0,_net.rxlen);
//	#ifdef _DEBUG_NET
//	Usart1_SendString(str);
//	#endif	
//	Net_SendString(str);
//}

//static u8 OpenTransmission(void)
//{
//	//设置透传模式
//	u8 cnt=2;
//	while(cnt--)
//	{
//        memset(_net.rxbuf,0,_net.rxlen);    
//        _net.SendString("AT+CIPMODE=1\r\n");  
//        if(FindStr((char*)_net.rxbuf,"OK",200)!=0)
//        {	
//			return 1;
//		}			
//	}
//	return 0;
//}
////退出透传
//static void CloseTransmission(void)
//{
//	_net.SendString("+++"); delay_ms(50);
//	_net.SendString("+++"); delay_ms(50);
//}


