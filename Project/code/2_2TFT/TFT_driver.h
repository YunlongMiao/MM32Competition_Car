
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   // ˫������ ���������� Ӳ������
*                   RD                  �鿴 zf_device_ips200.h �� IPS200_RD_PIN_PARALLEL8     �궨��
*                   WR                  �鿴 zf_device_ips200.h �� IPS200_WR_PIN_PARALLEL8     �궨��
*                   RS                  �鿴 zf_device_ips200.h �� IPS200_RS_PIN_PARALLEL8     �궨��
*                   RST                 �鿴 zf_device_ips200.h �� IPS200_RST_PIN_PARALLEL8    �궨��
*                   CS                  �鿴 zf_device_ips200.h �� IPS200_CS_PIN_PARALLEL8     �궨��
*                   BL                  �鿴 zf_device_ips200.h �� IPS200_BL_PIN_PARALLEL8     �궨��
*                   D0-D7               �鿴 zf_device_ips200.h �� IPS200_Dx_PIN_PARALLEL8     �궨��
*                   // �������� SPI ������ Ӳ������
*                   SCL                 �鿴 zf_device_ips200.h �� IPS200_SCL_PIN_SPI  �궨��
*                   SDA                 �鿴 zf_device_ips200.h �� IPS200_SDA_PIN_SPI  �궨��
*                   RST                 �鿴 zf_device_ips200.h �� IPS200_RST_PIN_SPI  �궨��
*                   DC                  �鿴 zf_device_ips200.h �� IPS200_DC_PIN_SPI   �궨��
*                   CS                  �鿴 zf_device_ips200.h �� IPS200_CS_PIN_SPI   �궨��
*                   BLk                 �鿴 zf_device_ips200.h �� IPS200_BLk_PIN_SPI  �궨��
*                   ��Դ����
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ���ֱ��� 320 * 240
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _TFT_DRIVER_H_
#define _TFT_DRIVER_H_

#include "zf_common_typedef.h"

#define USE_HARDWARE_SPI                  1
#define IPS200_USE_SOFT_SPI             ( 0 )                                   // Ĭ��ʹ��Ӳ�� SPI ��ʽ���� ����ʹ��Ӳ�� SPI ��ʽ����
#if IPS200_USE_SOFT_SPI                                                         // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� SPI ����====================================================
// ���ʹ�õ��ǵ��������������Ļ SPI ������������ �����޸�
#define IPS200_SOFT_SPI_DELAY           ( 1  )                                  // ��� SPI ��ʱ����ʱ���� ��ֵԽС SPI ͨ������Խ��
#define IPS200_SCL_PIN                  ( D4 )                                  // ��� SPI SCK ����
#define IPS200_SDA_PIN                  ( D6 )                                  // ��� SPI MOSI ����
//====================================================��� SPI ����====================================================
#else
//====================================================Ӳ�� SPI ����====================================================
// ���ʹ�õ��ǵ��������������Ļ SPI ������������ �����޸�
#define IPS200_SPI_SPEED                ( 60 * 1000 * 1000 )                    // Ӳ�� SPI ���� ��������Ϊϵͳʱ�Ӷ���Ƶ
#define IPS200_SPI                      ( SPI_3            )                    // Ӳ�� SPI ��
#define IPS200_SCL_PIN_SPI              ( SPI3_SCK_D4      )                    // Ӳ�� SPI SCK ����
#define IPS200_SDA_PIN_SPI              ( SPI3_MOSI_D6     )                    // Ӳ�� SPI MOSI ����
//====================================================Ӳ�� SPI ����====================================================
#endif
// ���ʹ�õ��ǵ��������������Ļ SPI ������������ �����޸�
#define IPS200_RST_PIN_SPI              ( D14 )                                 // Һ����λ���Ŷ���
#define IPS200_DC_PIN_SPI               ( D5  )                                 // Һ������λ���Ŷ���
#define IPS200_CS_PIN_SPI               ( D7  )
#define IPS200_BLk_PIN_SPI              ( D15 )

// ���ʹ�õ���˫�������������Ļ ���������������� �����޸�
#define IPS200_RD_PIN_PARALLEL8         ( D4  )
#define IPS200_WR_PIN_PARALLEL8         ( D6  )
#define IPS200_RS_PIN_PARALLEL8         ( D14 )
#define IPS200_RST_PIN_PARALLEL8        ( D5  )
#define IPS200_CS_PIN_PARALLEL8         ( D7  )
#define IPS200_BL_PIN_PARALLEL8         ( D15 )

// ���������������� �����޸� ��������Ļ��˫������ ����������õõ� ����Ҫ�����˸�����
#define IPS200_D0_PIN_PARALLEL8         ( G8  )
#define IPS200_D1_PIN_PARALLEL8         ( G9  )
#define IPS200_D2_PIN_PARALLEL8         ( G10 )
#define IPS200_D3_PIN_PARALLEL8         ( G11 )
#define IPS200_D4_PIN_PARALLEL8         ( G12 )
#define IPS200_D5_PIN_PARALLEL8         ( G13 )
#define IPS200_D6_PIN_PARALLEL8         ( G14 )
#define IPS200_D7_PIN_PARALLEL8         ( G15 )

#define IPS200_DEFAULT_DISPLAY_DIR      ( IPS200_PORTAIT   )                    // Ĭ�ϵ���ʾ����
#define IPS200_DEFAULT_PENCOLOR         ( RGB565_RED       )                    // Ĭ�ϵĻ�����ɫ
#define IPS200_DEFAULT_BGCOLOR          ( RGB565_WHITE     )                    // Ĭ�ϵı�����ɫ
#define IPS200_DEFAULT_DISPLAY_FONT     ( IPS200_8X16_FONT )                    // Ĭ�ϵ�����ģʽ

// ���ݶ�Ӧ��ַ ���ɸ���
#define IPS200_DATA_ADD                 gpio_odr_addr(IPS200_D0_PIN_PARALLEL8)

// �������
#define IPS200_RD(x)        ((x) ? (gpio_high(IPS200_RD_PIN_PARALLEL8)) : (gpio_low(IPS200_RD_PIN_PARALLEL8)))
#define IPS200_WR(x)        ((x) ? (gpio_high(IPS200_WR_PIN_PARALLEL8)) : (gpio_low(IPS200_WR_PIN_PARALLEL8)))
#define IPS200_RST(x)       ((x) ? (gpio_high(ips_rst_pin)) : (gpio_low(ips_rst_pin)))
#define IPS200_BL(x)        ((x) ? (gpio_high(ips_bl_pin)) : (gpio_low(ips_bl_pin)))
#define IPS200_RS(x)        ((x) ? (gpio_high(IPS200_RS_PIN_PARALLEL8)) : (gpio_low(IPS200_RS_PIN_PARALLEL8)))

#define IPS200_DC(x)        ((x) ? (gpio_high(IPS200_DC_PIN_SPI)) : (gpio_low(IPS200_DC_PIN_SPI)))
#define IPS200_CS(x)        ((x) ? (gpio_high(ips_cs_pin)) : (gpio_low(ips_cs_pin)))




//Һ�����ƿ���1�������궨��
#define	LCD_CS_SET  	IPS200_CS(1)   
#define	LCD_RS_SET  	IPS200_RS(1)   
//#define	LCD_SDA_SET  	LCD_CTRL->BSRR=LCD_SDA    
//#define	LCD_SCL_SET  	LCD_CTRL->BSRR=LCD_SCL    
#define	LCD_RST_SET  	IPS200_RST(1)    
#define	LCD_LED_SET  	IPS200_BL(1)  

//Һ�����ƿ���0�������궨��
#define	LCD_CS_CLR  	IPS200_CS(0)    
#define	LCD_RS_CLR  	IPS200_RS(0)    
//#define	LCD_SDA_CLR  	LCD_CTRL->BRR=LCD_SDA    
//#define	LCD_SCL_CLR  	LCD_CTRL->BRR=LCD_SCL    
#define	LCD_RST_CLR  	IPS200_RST(0)   
#define	LCD_LED_CLR  	IPS200_BL(0) 


//#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //�������
//#define LCD_DATAIN     LCD_DATA->IDR;   //��������

//#define LCD_WR_DATA(data){\
//LCD_RS_SET;\
//LCD_CS_CLR;\
//LCD_DATAOUT(data);\
//LCD_WR_CLR;\
//LCD_WR_SET;\
//LCD_CS_SET;\
//}



//-------------------------��Ļ������������--------------------------------------//
#define LCD_X_SIZE	        176
#define LCD_Y_SIZE	        220

/////////////////////////////////////�û�������///////////////////////////////////	 
//֧�ֺ��������ٶ����л�
#define USE_HORIZONTAL  		1	//�����Ƿ�ʹ�ú��� 		0,��ʹ��.1,ʹ��.

#ifdef USE_HORIZONTAL//��������˺��� 
#define X_MAX_PIXEL	        LCD_Y_SIZE
#define Y_MAX_PIXEL	        LCD_X_SIZE
#else
#define X_MAX_PIXEL	        LCD_X_SIZE
#define Y_MAX_PIXEL	        LCD_Y_SIZE
#endif


#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111



//typedef enum
//{
//    IPS200_TYPE_SPI,                                                            // SPI ����
//    IPS200_TYPE_PARALLEL8,                                                      // ��������
//}ips200_type_enum;

//typedef enum
//{
//    IPS200_PORTAIT                      = 0,                                    // ����ģʽ
//    IPS200_PORTAIT_180                  = 1,                                    // ����ģʽ  ��ת180
//    IPS200_CROSSWISE                    = 2,                                    // ����ģʽ
//    IPS200_CROSSWISE_180                = 3,                                    // ����ģʽ  ��ת180
//}ips200_dir_enum;

//typedef enum
//{
//    IPS200_6X8_FONT                     = 0,                                    // 6x8      ����
//    IPS200_8X16_FONT                    = 1,                                    // 8x16     ����
//    IPS200_16X16_FONT                   = 2,                                    // 16x16    ���� Ŀǰ��֧��
//}ips200_font_size_enum;





void ipsTFT_init ();
void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);
unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y);
void Lcd_SetRegion(uint8_t x_start,uint8_t y_start,uint8_t x_end,uint8_t y_end);
void Lcd_WriteData_16Bit(uint16_t Data);








////-------------------------------------------------------------------------------------------------------------------
//// �������     IPS200 ��ʾС���ͼ��
//// ����˵��     p               ͼ������
//// ����˵��     width           ��ʾ���
//// ����˵��     height          ��ʾ�߶�
//// ���ز���     void
//// ʹ��ʾ��     ips200_displayimage7725(ov7725_image_binary[0], 80, 60);
//// ��ע��Ϣ     
////-------------------------------------------------------------------------------------------------------------------
//#define ips200_displayimage7725(p, width, height)       (ips200_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))

////-------------------------------------------------------------------------------------------------------------------
//// �������     IPS200 ��ʾ�����ͼ�� ������ֵ�� ��ʾ�Ҷ�ͼ��
//// ����˵��     p               ͼ������
//// ����˵��     width           ��ʾ���
//// ����˵��     height          ��ʾ�߶�
//// ���ز���     void
//// ʹ��ʾ��     ips200_displayimage03x(mt9v03x_image[0], 94, 60);
//// ��ע��Ϣ     ���Ҫ��ʾ��ֵ��ͼ���ȥ���� ips200_show_gray_image ����
////-------------------------------------------------------------------------------------------------------------------
//#define ips200_displayimage03x(p, width, height)        (ips200_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))

////-------------------------------------------------------------------------------------------------------------------
//// �������     IPS200 ��ʾ��ͫͼ��
//// ����˵��     p               ͼ������
//// ����˵��     width           ��ʾ���
//// ����˵��     height          ��ʾ�߶�
//// ���ز���     void
//// ʹ��ʾ��     ips200_displayimage8660(scc8660_image[0], 80, 60);
//// ��ע��Ϣ     
////-------------------------------------------------------------------------------------------------------------------
//#define ips200_displayimage8660(p, width, height)       (ips200_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))

//void    ips200_init                     (ips200_type_enum type_select);

#endif
