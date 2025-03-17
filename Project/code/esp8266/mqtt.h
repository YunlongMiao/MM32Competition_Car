#ifndef __MQTT_H
#define __MQTT_H 			   
#include "stm32f10x.h"


/*
*以下参数需要用户自行修改才能测试用过
*/


#define User_ESP8266_SSID     "vivoS7t"    //wifi名
#define User_ESP8266_PWD      "qwertyuiopp"      //wifi密码

#define User_ESP8266_client_id    "k011hYO0ERp.ESP8266|securemode=2,signmethod=hmacsha256,timestamp=1690175733123|"   //MQTTclientID 用于标志client身份  最长256字节
#define User_ESP8266_username     "ESP8266&k011hYO0ERp"						//用于登录 MQTT 服务器 的 username, 最长 64 字节	
#define User_ESP8266_password			"8276752b9bc8446839bd2c78d3aaa4b43a44167a4682352741dcd9cc31b5c07b"          //用于登录 MQTT 服务器 的 password, 最长 64 字节
#define User_ESP8266_MQTTServer_IP     "iot-06z00c1xbz865fl.mqtt.iothub.aliyuncs.com"     //MQTT本地服务器IP
#define User_ESP8266_MQTTServer_PORT   1883     //服务器端口号
#define User_ESP8266_MQTTServer_Topic  "/sys/k011hYO0ERp/ESP8266/thing/service/property/set"    //订阅MQTT主题

void ESP8266_STA_MQTTClient_Test(void);

#endif
