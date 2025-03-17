
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   // 双排排针 并口两寸屏 硬件引脚
*                   RD                  查看 zf_device_ips200.h 中 IPS200_RD_PIN_PARALLEL8     宏定义
*                   WR                  查看 zf_device_ips200.h 中 IPS200_WR_PIN_PARALLEL8     宏定义
*                   RS                  查看 zf_device_ips200.h 中 IPS200_RS_PIN_PARALLEL8     宏定义
*                   RST                 查看 zf_device_ips200.h 中 IPS200_RST_PIN_PARALLEL8    宏定义
*                   CS                  查看 zf_device_ips200.h 中 IPS200_CS_PIN_PARALLEL8     宏定义
*                   BL                  查看 zf_device_ips200.h 中 IPS200_BL_PIN_PARALLEL8     宏定义
*                   D0-D7               查看 zf_device_ips200.h 中 IPS200_Dx_PIN_PARALLEL8     宏定义
*                   // 单排排针 SPI 两寸屏 硬件引脚
*                   SCL                 查看 zf_device_ips200.h 中 IPS200_SCL_PIN_SPI  宏定义
*                   SDA                 查看 zf_device_ips200.h 中 IPS200_SDA_PIN_SPI  宏定义
*                   RST                 查看 zf_device_ips200.h 中 IPS200_RST_PIN_SPI  宏定义
*                   DC                  查看 zf_device_ips200.h 中 IPS200_DC_PIN_SPI   宏定义
*                   CS                  查看 zf_device_ips200.h 中 IPS200_CS_PIN_SPI   宏定义
*                   BLk                 查看 zf_device_ips200.h 中 IPS200_BLk_PIN_SPI  宏定义
*                   电源引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   最大分辨率 320 * 240
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _TFT_DRIVER_H_
#define _TFT_DRIVER_H_

#include "zf_common_typedef.h"

#define USE_HARDWARE_SPI                  1
#define IPS200_USE_SOFT_SPI             ( 0 )                                   // 默认使用硬件 SPI 方式驱动 建议使用硬件 SPI 方式驱动
#if IPS200_USE_SOFT_SPI                                                         // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 SPI 驱动====================================================
// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_SOFT_SPI_DELAY           ( 1  )                                  // 软件 SPI 的时钟延时周期 数值越小 SPI 通信速率越快
#define IPS200_SCL_PIN                  ( D4 )                                  // 软件 SPI SCK 引脚
#define IPS200_SDA_PIN                  ( D6 )                                  // 软件 SPI MOSI 引脚
//====================================================软件 SPI 驱动====================================================
#else
//====================================================硬件 SPI 驱动====================================================
// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_SPI_SPEED                ( 60 * 1000 * 1000 )                    // 硬件 SPI 速率 这里设置为系统时钟二分频
#define IPS200_SPI                      ( SPI_3            )                    // 硬件 SPI 号
#define IPS200_SCL_PIN_SPI              ( SPI3_SCK_D4      )                    // 硬件 SPI SCK 引脚
#define IPS200_SDA_PIN_SPI              ( SPI3_MOSI_D6     )                    // 硬件 SPI MOSI 引脚
//====================================================硬件 SPI 驱动====================================================
#endif
// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_RST_PIN_SPI              ( D14 )                                 // 液晶复位引脚定义
#define IPS200_DC_PIN_SPI               ( D5  )                                 // 液晶命令位引脚定义
#define IPS200_CS_PIN_SPI               ( D7  )
#define IPS200_BLk_PIN_SPI              ( D15 )

// 如果使用的是双排排针的两寸屏幕 并口驱动控制引脚 可以修改
#define IPS200_RD_PIN_PARALLEL8         ( D4  )
#define IPS200_WR_PIN_PARALLEL8         ( D6  )
#define IPS200_RS_PIN_PARALLEL8         ( D14 )
#define IPS200_RST_PIN_PARALLEL8        ( D5  )
#define IPS200_CS_PIN_PARALLEL8         ( D7  )
#define IPS200_BL_PIN_PARALLEL8         ( D15 )

// 并口驱动数据引脚 可以修改 如果你的屏幕是双排排针 这里的引脚用得到 必须要连续八个引脚
#define IPS200_D0_PIN_PARALLEL8         ( G8  )
#define IPS200_D1_PIN_PARALLEL8         ( G9  )
#define IPS200_D2_PIN_PARALLEL8         ( G10 )
#define IPS200_D3_PIN_PARALLEL8         ( G11 )
#define IPS200_D4_PIN_PARALLEL8         ( G12 )
#define IPS200_D5_PIN_PARALLEL8         ( G13 )
#define IPS200_D6_PIN_PARALLEL8         ( G14 )
#define IPS200_D7_PIN_PARALLEL8         ( G15 )

#define IPS200_DEFAULT_DISPLAY_DIR      ( IPS200_PORTAIT   )                    // 默认的显示方向
#define IPS200_DEFAULT_PENCOLOR         ( RGB565_RED       )                    // 默认的画笔颜色
#define IPS200_DEFAULT_BGCOLOR          ( RGB565_WHITE     )                    // 默认的背景颜色
#define IPS200_DEFAULT_DISPLAY_FONT     ( IPS200_8X16_FONT )                    // 默认的字体模式

// 数据对应地址 不可更改
#define IPS200_DATA_ADD                 gpio_odr_addr(IPS200_D0_PIN_PARALLEL8)

// 控制语句
#define IPS200_RD(x)        ((x) ? (gpio_high(IPS200_RD_PIN_PARALLEL8)) : (gpio_low(IPS200_RD_PIN_PARALLEL8)))
#define IPS200_WR(x)        ((x) ? (gpio_high(IPS200_WR_PIN_PARALLEL8)) : (gpio_low(IPS200_WR_PIN_PARALLEL8)))
#define IPS200_RST(x)       ((x) ? (gpio_high(ips_rst_pin)) : (gpio_low(ips_rst_pin)))
#define IPS200_BL(x)        ((x) ? (gpio_high(ips_bl_pin)) : (gpio_low(ips_bl_pin)))
#define IPS200_RS(x)        ((x) ? (gpio_high(IPS200_RS_PIN_PARALLEL8)) : (gpio_low(IPS200_RS_PIN_PARALLEL8)))

#define IPS200_DC(x)        ((x) ? (gpio_high(IPS200_DC_PIN_SPI)) : (gpio_low(IPS200_DC_PIN_SPI)))
#define IPS200_CS(x)        ((x) ? (gpio_high(ips_cs_pin)) : (gpio_low(ips_cs_pin)))




//液晶控制口置1操作语句宏定义
#define	LCD_CS_SET  	IPS200_CS(1)   
#define	LCD_RS_SET  	IPS200_RS(1)   
//#define	LCD_SDA_SET  	LCD_CTRL->BSRR=LCD_SDA    
//#define	LCD_SCL_SET  	LCD_CTRL->BSRR=LCD_SCL    
#define	LCD_RST_SET  	IPS200_RST(1)    
#define	LCD_LED_SET  	IPS200_BL(1)  

//液晶控制口置0操作语句宏定义
#define	LCD_CS_CLR  	IPS200_CS(0)    
#define	LCD_RS_CLR  	IPS200_RS(0)    
//#define	LCD_SDA_CLR  	LCD_CTRL->BRR=LCD_SDA    
//#define	LCD_SCL_CLR  	LCD_CTRL->BRR=LCD_SCL    
#define	LCD_RST_CLR  	IPS200_RST(0)   
#define	LCD_LED_CLR  	IPS200_BL(0) 


//#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
//#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入

//#define LCD_WR_DATA(data){\
//LCD_RS_SET;\
//LCD_CS_CLR;\
//LCD_DATAOUT(data);\
//LCD_WR_CLR;\
//LCD_WR_SET;\
//LCD_CS_SET;\
//}



//-------------------------屏幕物理像素设置--------------------------------------//
#define LCD_X_SIZE	        176
#define LCD_Y_SIZE	        220

/////////////////////////////////////用户配置区///////////////////////////////////	 
//支持横竖屏快速定义切换
#define USE_HORIZONTAL  		1	//定义是否使用横屏 		0,不使用.1,使用.

#ifdef USE_HORIZONTAL//如果定义了横屏 
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
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111



//typedef enum
//{
//    IPS200_TYPE_SPI,                                                            // SPI 驱动
//    IPS200_TYPE_PARALLEL8,                                                      // 并口驱动
//}ips200_type_enum;

//typedef enum
//{
//    IPS200_PORTAIT                      = 0,                                    // 竖屏模式
//    IPS200_PORTAIT_180                  = 1,                                    // 竖屏模式  旋转180
//    IPS200_CROSSWISE                    = 2,                                    // 横屏模式
//    IPS200_CROSSWISE_180                = 3,                                    // 横屏模式  旋转180
//}ips200_dir_enum;

//typedef enum
//{
//    IPS200_6X8_FONT                     = 0,                                    // 6x8      字体
//    IPS200_8X16_FONT                    = 1,                                    // 8x16     字体
//    IPS200_16X16_FONT                   = 2,                                    // 16x16    字体 目前不支持
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
//// 函数简介     IPS200 显示小钻风图像
//// 参数说明     p               图像数组
//// 参数说明     width           显示宽度
//// 参数说明     height          显示高度
//// 返回参数     void
//// 使用示例     ips200_displayimage7725(ov7725_image_binary[0], 80, 60);
//// 备注信息     
////-------------------------------------------------------------------------------------------------------------------
//#define ips200_displayimage7725(p, width, height)       (ips200_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))

////-------------------------------------------------------------------------------------------------------------------
//// 函数简介     IPS200 显示总钻风图像 不带二值化 显示灰度图像
//// 参数说明     p               图像数组
//// 参数说明     width           显示宽度
//// 参数说明     height          显示高度
//// 返回参数     void
//// 使用示例     ips200_displayimage03x(mt9v03x_image[0], 94, 60);
//// 备注信息     如果要显示二值化图像就去调用 ips200_show_gray_image 函数
////-------------------------------------------------------------------------------------------------------------------
//#define ips200_displayimage03x(p, width, height)        (ips200_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))

////-------------------------------------------------------------------------------------------------------------------
//// 函数简介     IPS200 显示凌瞳图像
//// 参数说明     p               图像数组
//// 参数说明     width           显示宽度
//// 参数说明     height          显示高度
//// 返回参数     void
//// 使用示例     ips200_displayimage8660(scc8660_image[0], 80, 60);
//// 备注信息     
////-------------------------------------------------------------------------------------------------------------------
//#define ips200_displayimage8660(p, width, height)       (ips200_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))

//void    ips200_init                     (ips200_type_enum type_select);

#endif
