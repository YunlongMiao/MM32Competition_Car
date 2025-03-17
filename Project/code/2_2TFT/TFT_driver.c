
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
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*
*                   // �������� SPI ������ Ӳ������
*                   SCL                 �鿴 zf_device_ips200.h �� IPS200_SCL_PIN_SPI  �궨��
*                   SDA                 �鿴 zf_device_ips200.h �� IPS200_SDA_PIN_SPI  �궨��
*                   RST                 �鿴 zf_device_ips200.h �� IPS200_RST_PIN_SPI  �궨��
*                   DC                  �鿴 zf_device_ips200.h �� IPS200_DC_PIN_SPI   �궨��
*                   CS                  �鿴 zf_device_ips200.h �� IPS200_CS_PIN_SPI   �궨��
*                   BLk                 �鿴 zf_device_ips200.h �� IPS200_BLk_PIN_SPI  �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ���ֱ��� 320 * 240
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"

#include "TFT_driver.h"

//static uint16                   ips200_pencolor         = IPS200_DEFAULT_PENCOLOR;
//static uint16                   ips200_bgcolor          = IPS200_DEFAULT_BGCOLOR;

//static ips200_type_enum         ips200_display_type     = IPS200_TYPE_SPI;
//static ips200_dir_enum          ips200_display_dir      = IPS200_DEFAULT_DISPLAY_DIR;
//static ips200_font_size_enum    ips200_display_font     = IPS200_DEFAULT_DISPLAY_FONT;

//static uint16                   ips200_x_max            = 240;
//static uint16                   ips200_y_max            = 320;

static gpio_pin_enum            ips_rst_pin             = IPS200_RST_PIN_SPI;
static gpio_pin_enum            ips_bl_pin              = IPS200_BLk_PIN_SPI;
static gpio_pin_enum            ips_cs_pin              = IPS200_CS_PIN_SPI;

#if IPS200_USE_SOFT_SPI
static soft_spi_info_struct                 ips200_spi;
//-------------------------------------------------------------------------------------------------------------------
// �������     IPS200 SPI д 8bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips200_write_8bit_data_spi(command);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define ips200_write_8bit_data_spi(data)    (soft_spi_write_8bit(&ips200_spi, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS200 SPI д 16bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips200_write_16bit_data_spi(dat);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define ips200_write_16bit_data_spi(data)   (soft_spi_write_16bit(&ips200_spi, (data)))
#else
//-------------------------------------------------------------------------------------------------------------------
// �������     IPS200 SPI д 8bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips200_write_8bit_data_spi(command);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define SPI_WriteByte(data)    (spi_write_8bit(IPS200_SPI, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS200 SPI д 16bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips200_write_16bit_data_spi(dat);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define ips200_write_16bit_data_spi(data)   (spi_write_16bit(IPS200_SPI, (data)))
#endif




/****************************************************************************
* ��    �ƣ�Lcd_WriteIndex(uint8_t Index)
* ��    �ܣ���Һ����дһ��8λָ��
* ��ڲ�����Index   �Ĵ�����ַ
* ���ڲ�������
* ˵    ��������ǰ����ѡ�п��������ڲ�����
****************************************************************************/
void Lcd_WriteIndex(uint8_t Index)
{
   LCD_CS_CLR;
   LCD_RS_CLR;
#if USE_HARDWARE_SPI   
   SPI_WriteByte(Index);
#else
   SPIv_WriteData(Index);
#endif 
   LCD_CS_SET;
}

/****************************************************************************
* ��    �ƣ�Lcd_WriteData(uint8_t Data)
* ��    �ܣ���Һ����дһ��8λ����
* ��ڲ�����dat     �Ĵ�������
* ���ڲ�������
* ˵    �����������ָ����ַд�����ݣ��ڲ�����
****************************************************************************/
void Lcd_WriteData(uint8_t Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
#if USE_HARDWARE_SPI   
   SPI_WriteByte(Data);
#else
   SPIv_WriteData(Data);
#endif 
   LCD_CS_SET;
}


/****************************************************************************
* ��    �ƣ�void Lcd_WriteData_16Bit(uint16_t Data)
* ��    �ܣ���Һ����дһ��16λ����
* ��ڲ�����Data
* ���ڲ�������
* ˵    �����������ָ����ַд��һ��16λ����
****************************************************************************/
void Lcd_WriteData_16Bit(uint16_t Data)
{	
	Lcd_WriteData(Data>>8);
	Lcd_WriteData(Data);	
}



/****************************************************************************
* ��    �ƣ�void LCD_WriteReg(uint8_t Index,uint16_t Data)
* ��    �ܣ�д�Ĵ�������
* ��ڲ�����Index,Data
* ���ڲ�������
* ˵    ����������Ϊ��Ϻ�������Index��ַ�ļĴ���д��Dataֵ
****************************************************************************/
void LCD_WriteReg(uint8_t Index,uint16_t Data)
{
	Lcd_WriteIndex(Index);
  	Lcd_WriteData_16Bit(Data);
}



/****************************************************************************
* ��    �ƣ�void Lcd_Reset(void)
* ��    �ܣ�Һ��Ӳ��λ����
* ��ڲ�������
* ���ڲ�������
* ˵    ����Һ����ʼ��ǰ��ִ��һ�θ�λ����
****************************************************************************/
void Lcd_Reset(void)
{
	LCD_RST_CLR;
	system_delay_ms(100);
	LCD_RST_SET;
	system_delay_ms(50);
}




//-------------------------------------------------------------------------------------------------------------------
// �������     2�� IPSҺ����ʼ��
// ����˵��     type_select     �������ӿ����� IPS200_TYPE_SPI Ϊ SPI �ӿڴ��������� IPS200_TYPE_PARALLEL8 Ϊ 8080 Э���λ����������
// ���ز���     void
// ʹ��ʾ��     ips200_init(IPS200_TYPE_PARALLEL8);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
//void SPI2_Init (ips200_type_enum type_select)
void ipsTFT_init ()
{
    if(1)
    {
        ips_rst_pin = IPS200_RST_PIN_SPI;
        ips_bl_pin =  IPS200_BLk_PIN_SPI;
        ips_cs_pin =  IPS200_CS_PIN_SPI;
#if IPS200_USE_SOFT_SPI
        soft_spi_init(&ips200_spi, 0, IPS200_SOFT_SPI_DELAY, IPS200_SCL_PIN, IPS200_SDA_PIN, SOFT_SPI_PIN_NULL, SOFT_SPI_PIN_NULL);
#else
        spi_init(IPS200_SPI, SPI_MODE0, IPS200_SPI_SPEED, IPS200_SCL_PIN_SPI, IPS200_SDA_PIN_SPI, SPI_MISO_NULL, SPI_CS_NULL);
#endif

        gpio_init(IPS200_DC_PIN_SPI, GPO, GPIO_LOW, GPO_PUSH_PULL);
        gpio_init(ips_rst_pin, GPO, GPIO_LOW, GPO_PUSH_PULL);
        gpio_init(ips_cs_pin, GPO, GPIO_HIGH, GPO_PUSH_PULL);
        gpio_init(ips_bl_pin, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    }
 
   
}






/****************************************************************************
* ��    �ƣ�void Lcd_Init(void)
* ��    �ܣ�Һ����ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����Һ����ʼ��_ILI9225_176X220
****************************************************************************/
void Lcd_Init()
{	
#if USE_HARDWARE_SPI //ʹ��Ӳ��SPI
	ipsTFT_init();
#else	
	LCD_GPIO_Init();//ʹ��ģ��SPI
#endif
	Lcd_Reset(); //Reset before LCD Init.

	//LCD Init For 2.2inch LCD Panel with ILI9225.	
	LCD_WriteReg(0x10, 0x0000); // Set SAP,DSTB,STB
	LCD_WriteReg(0x11, 0x0000); // Set APON,PON,AON,VCI1EN,VC
	LCD_WriteReg(0x12, 0x0000); // Set BT,DC1,DC2,DC3
	LCD_WriteReg(0x13, 0x0000); // Set GVDD
	LCD_WriteReg(0x14, 0x0000); // Set VCOMH/VCOML voltage
	system_delay_ms(40); // Delay 20 ms
	
	// Please follow this power on sequence
	LCD_WriteReg(0x11, 0x0018); // Set APON,PON,AON,VCI1EN,VC
	LCD_WriteReg(0x12, 0x1121); // Set BT,DC1,DC2,DC3
	LCD_WriteReg(0x13, 0x0063); // Set GVDD
	LCD_WriteReg(0x14, 0x3961); // Set VCOMH/VCOML voltage
	LCD_WriteReg(0x10, 0x0800); // Set SAP,DSTB,STB
	system_delay_ms(10); // Delay 10 ms
	LCD_WriteReg(0x11, 0x1038); // Set APON,PON,AON,VCI1EN,VC
	system_delay_ms(30); // Delay 30 ms
	
	
	LCD_WriteReg(0x02, 0x0100); // set 1 line inversion

#if USE_HORIZONTAL//��������˺���
	//R01H:SM=0,GS=0,SS=0 (for details,See the datasheet of ILI9225)
	LCD_WriteReg(0x01, 0x001C); // set the display line number and display direction
	//R03H:BGR=1,ID0=1,ID1=1,AM=1 (for details,See the datasheet of ILI9225)
	LCD_WriteReg(0x03, 0x1038); // set GRAM write direction .
#else//����
	//R01H:SM=0,GS=0,SS=1 (for details,See the datasheet of ILI9225)
	LCD_WriteReg(0x01, 0x011C); // set the display line number and display direction 
	//R03H:BGR=1,ID0=1,ID1=1,AM=0 (for details,See the datasheet of ILI9225)
	LCD_WriteReg(0x03, 0x1030); // set GRAM write direction.
#endif

	LCD_WriteReg(0x07, 0x0000); // Display off
	LCD_WriteReg(0x08, 0x0808); // set the back porch and front porch
	LCD_WriteReg(0x0B, 0x1100); // set the clocks number per line
	LCD_WriteReg(0x0C, 0x0000); // CPU interface
	LCD_WriteReg(0x0F, 0x0501); // Set Osc
	LCD_WriteReg(0x15, 0x0020); // Set VCI recycling
	LCD_WriteReg(0x20, 0x0000); // RAM Address
	LCD_WriteReg(0x21, 0x0000); // RAM Address
	
	//------------------------ Set GRAM area --------------------------------//
	LCD_WriteReg(0x30, 0x0000); 
	LCD_WriteReg(0x31, 0x00DB); 
	LCD_WriteReg(0x32, 0x0000); 
	LCD_WriteReg(0x33, 0x0000); 
	LCD_WriteReg(0x34, 0x00DB); 
	LCD_WriteReg(0x35, 0x0000); 
	LCD_WriteReg(0x36, 0x00AF); 
	LCD_WriteReg(0x37, 0x0000); 
	LCD_WriteReg(0x38, 0x00DB); 
	LCD_WriteReg(0x39, 0x0000); 
	
	
	// ---------- Adjust the Gamma 2.2 Curve -------------------//
	LCD_WriteReg(0x50, 0x0603); 
	LCD_WriteReg(0x51, 0x080D); 
	LCD_WriteReg(0x52, 0x0D0C); 
	LCD_WriteReg(0x53, 0x0205); 
	LCD_WriteReg(0x54, 0x040A); 
	LCD_WriteReg(0x55, 0x0703); 
	LCD_WriteReg(0x56, 0x0300); 
	LCD_WriteReg(0x57, 0x0400); 
	LCD_WriteReg(0x58, 0x0B00); 
	LCD_WriteReg(0x59, 0x0017); 
	
	
	
	LCD_WriteReg(0x0F, 0x0701); // Vertical RAM Address Position
	LCD_WriteReg(0x07, 0x0012); // Vertical RAM Address Position
	system_delay_ms(50); // Delay 50 ms
	LCD_WriteReg(0x07, 0x1017); // Vertical RAM Address Position  
	
}



/*************************************************
��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void Lcd_SetXY(uint16_t Xpos, uint16_t Ypos)
{	
#if USE_HORIZONTAL//��������˺���  	    	
	LCD_WriteReg(0x21,Xpos);
	LCD_WriteReg(0x20,Ypos);
#else//����	
	LCD_WriteReg(0x20,Xpos);
	LCD_WriteReg(0x21,Ypos);
#endif
	Lcd_WriteIndex(0x22);		
} 
/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
*************************************************/
//������ʾ����
void Lcd_SetRegion(uint8_t xStar, uint8_t yStar,uint8_t xEnd,uint8_t yEnd)
{
#if USE_HORIZONTAL//��������˺���	
	LCD_WriteReg(0x38,xEnd);
	LCD_WriteReg(0x39,xStar);
	LCD_WriteReg(0x36,yEnd);
	LCD_WriteReg(0x37,yStar);
	LCD_WriteReg(0x21,xStar);
	LCD_WriteReg(0x20,yStar);
#else//����	
	LCD_WriteReg(0x36,xEnd);
	LCD_WriteReg(0x37,xStar);
	LCD_WriteReg(0x38,yEnd);
	LCD_WriteReg(0x39,yStar);
	LCD_WriteReg(0x20,xStar);
	LCD_WriteReg(0x21,yStar);
#endif
	Lcd_WriteIndex(0x22);	
}

	
/*************************************************
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�����xy�������ɫ����
����ֵ����
*************************************************/
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	Lcd_SetXY(x,y);
	Lcd_WriteData_16Bit(Data);

}    

/*************************************************
��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
*************************************************/
void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	Lcd_WriteData_16Bit(Color);
    }   
}






