#ifndef __ESP8266_H
#define __ESP8266_H 			   


//#define u8 unsigned char
//#define u16 unsigned int
//	

//typedef struct
//{
//	u8 *rxbuf;u16 rxlen;
//	u8 *txbuf;u16 txlen;
//	
//	u8 (*Check)(void);
//	u8 (*Init)(u8 *prx,u16 rxlen,u8 *ptx,u16 txlen);
//	void (*Restore)(void);
//	u8 (*ConnectAP)(char *ssid,char *pswd);
//	u8 (*ConnectServer)(char* mode,char *ip,u16 port);
//	u8 (*DisconnectServer)(void);
//	u8 (*OpenTransmission)(void);
//	void (*CloseTransmission)(void);		
//	void (*SendString)(char *str);
//	void (*SendBuf)(u8 *buf,u16 len);
//}_typdef_net;
void ESP_Init();
void Get_Sensing();

#endif
