#ifndef __MQTT_H
#define __MQTT_H 			   
#include "stm32f10x.h"


/*
*���²�����Ҫ�û������޸Ĳ��ܲ����ù�
*/


#define User_ESP8266_SSID     "vivoS7t"    //wifi��
#define User_ESP8266_PWD      "qwertyuiopp"      //wifi����

#define User_ESP8266_client_id    "k011hYO0ERp.ESP8266|securemode=2,signmethod=hmacsha256,timestamp=1690175733123|"   //MQTTclientID ���ڱ�־client���  �256�ֽ�
#define User_ESP8266_username     "ESP8266&k011hYO0ERp"						//���ڵ�¼ MQTT ������ �� username, � 64 �ֽ�	
#define User_ESP8266_password			"8276752b9bc8446839bd2c78d3aaa4b43a44167a4682352741dcd9cc31b5c07b"          //���ڵ�¼ MQTT ������ �� password, � 64 �ֽ�
#define User_ESP8266_MQTTServer_IP     "iot-06z00c1xbz865fl.mqtt.iothub.aliyuncs.com"     //MQTT���ط�����IP
#define User_ESP8266_MQTTServer_PORT   1883     //�������˿ں�
#define User_ESP8266_MQTTServer_Topic  "/sys/k011hYO0ERp/ESP8266/thing/service/property/set"    //����MQTT����

void ESP8266_STA_MQTTClient_Test(void);

#endif
