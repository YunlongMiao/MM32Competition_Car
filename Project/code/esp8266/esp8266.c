#include "esp8266.h"
#include "zf_device_wifi_uart.h"
#include "zf_driver_uart.h"
#include "sensing_control.h"
#include "zf_common_debug.h"

//void ESP_Init(){

//	 uart_init(WIFI_UART_INDEX, 115200, WIFI_UART_RX_PIN, WIFI_UART_TX_PIN);     // ��ʼ��WiFiģ����ʹ�õĴ���
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
//�궨��
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
////	// �˴���д�û����� ���������ʼ�������
////    printf("\r\n Wi-Fi UART init.");

////    // ��ǰʹ�õ��� WIFI ����ģ��� station ģʽ ������������·���� WIFI
////    // 
////    // �������ݷ�ʽ����ʹ�������(Ĭ��) Ҳ����ʹ��͸������ ������ wifi_uart_init �������޸� <��ģ����Ϊ������ʱ ֻ��ʹ�����ʽ��������>
////    while(wifi_uart_init(WIFI_SSID_TEST, WIFI_PASSWORD_TEST, WIFI_UART_STATION))	//����ģʽ��ʼ��
////    {
////        system_delay_ms(500);                                                   // ��ʼ��ʧ�� �ȴ� 500ms
////    }
////		
////		printf("\r\n module version:%s",wifi_uart_information.wifi_uart_version);   // ģ��̼��汾
////    printf("\r\n module mac    :%s",wifi_uart_information.wifi_uart_mac);       // ģ�� MAC ��Ϣ
////    printf("\r\n module ip     :%s",wifi_uart_information.wifi_uart_local_ip);  // ģ�� IP ��ַ
////    printf("\r\n module port   :%s",wifi_uart_information.wifi_uart_local_port);// ģ�� PORT ��Ϣ
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
// * ���ܣ��ָ���������
// * ������None
// * ����ֵ��None
// * ˵��:��ʱESP8266�е��û����ý�ȫ����ʧ�ظ��ɳ���״̬
// */
//static void Restore(void)
//{
//	_net.CloseTransmission();           //�˳�͸��
//    delay_ms(500);
//	_net.SendString("AT+RESTORE\r\n");//�ָ����� 	
////    NVIC_SystemReset();                 //ͬʱ������Ƭ��   
//}


///**
// * ���ܣ����ESP8266�Ƿ�����
// * ������None
// * ����ֵ��ESP8266����״̬
// *        ��0 ESP8266����
// *        0 ESP8266������  
// */
//static unsigned char Check(void)
//{
//	unsigned char check_cnt=5;
//	while(check_cnt--)
//	{
//		memset(_net.rxbuf,0,_net.rxlen); 	 //��ս��ջ���
//		_net.SendString("AT\r\n");     		 //����AT����ָ��	
//		if(FindStr((char*)_net.rxbuf,"OK",200) != 0)
//		{
//			return 1;
//		}
//	}
//	return 0;
//}





///**
// * ���ܣ������ȵ�
// * ������
// *         ssid:�ȵ���
// *         pwd:�ȵ�����
// * ����ֵ��
// *         ���ӽ��,��0���ӳɹ�,0����ʧ��
// * ˵���� 
// *         ʧ�ܵ�ԭ�������¼���(UARTͨ�ź�ESP8266���������)
// *         1. WIFI�������벻��ȷ
// *         2. ·���������豸̫��,δ�ܸ�ESP8266����IP
// */
//static u8 ConnectAP(char* ssid,char* pswd)
//{
//	u8 cnt=5;
//	while(cnt--)
//	{
//		memset(_net.rxbuf,0,_net.rxlen);     
//		_net.SendString("AT+CWMODE_CUR=1\r\n");              //����ΪSTATIONģʽ	
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
//		memset(_net.txbuf,0,_net.txlen);                            //��շ��ͻ���
//		memset(_net.rxbuf,0,_net.rxlen);                            //��ս��ջ���
//		sprintf((char*)_net.txbuf,"AT+CWJAP_CUR=\"%s\",\"%s\"\r\n",ssid,pswd);//����Ŀ��AP
//		_net.SendString((char*)_net.txbuf);	
//		if(FindStr((char*)_net.rxbuf,"OK",8000)!=0)                      //���ӳɹ��ҷ��䵽IP
//		{
//			return 1;
//		}
//	}
//	return 0;
//}





///**
// * ���ܣ�ʹ��ָ��Э��(TCP/UDP)���ӵ�������
// * ������
// *         mode:Э������ "TCP","UDP"
// *         ip:Ŀ�������IP
// *         port:Ŀ���Ƿ������˿ں�
// * ����ֵ��
// *         ���ӽ��,��0���ӳɹ�,0����ʧ��
// * ˵���� 
// *         ʧ�ܵ�ԭ�������¼���(UARTͨ�ź�ESP8266���������)
// *         1. Զ�̷�����IP�Ͷ˿ں�����
// *         2. δ����AP
// *         3. �������˽�ֹ���(һ�㲻�ᷢ��)
// */
//static u8 ConnectServer(char* mode,char* ip,u16 port)
//{
//	u8 cnt;
//   
//    _net.CloseTransmission();                   //����������˳�͸��
//    delay_ms(500);

//	//���ӷ�����
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
//	//����͸��ģʽ
//	if(_net.OpenTransmission()==0) return 0;
//	
//	//��������״̬
//	cnt=2;
//	while(cnt--)
//	{
//		memset(_net.rxbuf,0,_net.rxlen); 
//		_net.SendString("AT+CIPSEND\r\n");//��ʼ����͸������״̬
//		if(FindStr((char*)_net.rxbuf,">",200)!=0)
//		{
//			return 1;
//		}
//	}
//	return 0;
//}




///**
// * ���ܣ������ͷ������Ͽ�����
// * ������None
// * ����ֵ��
// *         ���ӽ��,��0�Ͽ��ɹ�,0�Ͽ�ʧ��
// */
//static u8 DisconnectServer(void)
//{
//	u8 cnt;
//    _net.CloseTransmission();	//�˳�͸��
//    delay_ms(500);
//	while(cnt--)
//	{
//		memset(_net.rxbuf,0,_net.rxlen);  
//		_net.SendString("AT+CIPCLOSE\r\n");//�ر�����

//		if(FindStr((char*)_net.rxbuf,"CLOSED",200)!=0)//�����ɹ�,�ͷ������ɹ��Ͽ�
//		{
//			break;
//		}
//	}
//	if(cnt) return 1;
//	return 0;
//}



///**
// * ���ܣ�͸��ģʽ�µ����ݷ��ͺ���
// * ������
// *      buffer:����������
// * ����ֵ��None
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
// * ���ܣ�͸��ģʽ�µ����ݷ��ͺ���
// * ������
// *      buffer:����������
// * ����ֵ��None
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
//	//����͸��ģʽ
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
////�˳�͸��
//static void CloseTransmission(void)
//{
//	_net.SendString("+++"); delay_ms(50);
//	_net.SendString("+++"); delay_ms(50);
//}


