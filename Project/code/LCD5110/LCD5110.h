/*******************************************************************************
 ************************* QQ858860583 *****************************************
 ************************* 正点原子论坛号：cornrn ******************************	
 *******************************************************************************/
#ifndef _LCD5110_H
#define _LCD5110_H

#include "zf_common_typedef.h"
#include "hal_common.h"
#include "hal_gpio.h"
#include "zf_driver_delay.h"	
	
/******************************宽高像素 ******************************/
#define LCD_X_RES		84
#define LCD_Y_RES		48 
/**************************枚举 D/C模式选择 **************************/
typedef enum
{
  DC_CMD  = 0,	//写命令
	DC_DATA = 1		//写数据	
} DCType;
/**********************管脚配置 H: high, L: low***********************/
#define LCD_CTRL_PORT	GPIOD
#define LCD_RST			  GPIO_PIN_7
#define LCD_CE			  GPIO_PIN_5
#define LCD_DC			  GPIO_PIN_14

 
/***************************config as spi2 ***************************/

#define LCD_CLK			  GPIO_PIN_4
#define LCD_MOSI		  GPIO_PIN_6

#define LCD_RST_H()		GPIO_SetBits  (LCD_CTRL_PORT, LCD_RST)
#define LCD_RST_L()		GPIO_ClearBits(LCD_CTRL_PORT, LCD_RST)
#define LCD_CE_H()		GPIO_SetBits  (LCD_CTRL_PORT, LCD_CE)
#define LCD_CE_L()		GPIO_ClearBits(LCD_CTRL_PORT, LCD_CE)
#define LCD_DC_DATA()	GPIO_SetBits  (LCD_CTRL_PORT, LCD_DC)
#define LCD_DC_CMD()	GPIO_ClearBits(LCD_CTRL_PORT, LCD_DC)
#define LCD_MOSI_H()	GPIO_SetBits  (LCD_CTRL_PORT, LCD_MOSI)
#define LCD_MOSI_L()	GPIO_ClearBits(LCD_CTRL_PORT, LCD_MOSI)
#define LCD_CLK_H()		GPIO_SetBits  (LCD_CTRL_PORT, LCD_CLK)
#define LCD_CLK_L()		GPIO_ClearBits(LCD_CTRL_PORT, LCD_CLK)
 

/************************函数定义****************************/

void LCD5110_Init(void);
void LCD_Clear(void);
//void LCD_SetXY(uint8_t X, uint8_t Y);
void LCD_SetXY(uint8_t Y, uint8_t X);
void LCD_SetContrast(uint8_t contrast);
void LCD_Send(uint8_t data, DCType dc);
void LCD_Write_Char(uint8_t ascii);
//void LCD_Write_EnStr(uint8_t X, uint8_t Y, uint8_t* s);
void LCD_Write_EnStr(uint8_t X, uint8_t Y, char* s);		//字符串
void LCD_Write_Hanzi(uint8_t X, uint8_t Y,uint8_t GBK);
void LCD5110_IO_Configuration(void);
void LCD_Write_FloatNum(uint8_t X, uint8_t Y, float s);	//浮点数
void LCD_Write_IntNum(uint8_t X, uint8_t Y, int s);

#define puts_xy(x,y,s) LCD_Write_EnStr(x, y, s)

#endif

