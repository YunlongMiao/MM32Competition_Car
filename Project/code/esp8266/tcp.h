#ifndef __TCP_H
#define __TCP_H 			   
#include "stm32f10x.h"


/*
*���²�����Ҫ�û������޸Ĳ��ܲ����ù�
*/

#define User_ESP8266_SSID     "vivoS7t"          //wifi��
#define User_ESP8266_PWD      "qwertyuiopp"      //wifi����

#define User_ESP8266_TCPServer_IP     "192.168.127.128"     //������IP
#define User_ESP8266_TCPServer_PORT   "1347"      //�������˿ں�


extern volatile uint8_t TcpClosedFlag;  //����״̬��־

void ESP8266_STA_TCPClient_Test(void);

#endif
