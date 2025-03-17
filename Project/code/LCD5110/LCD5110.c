
/*******************************************************************************
 ************************* QQ858860583 *****************************************
 ************************* 正点原子论坛号：cornrn ******************************	
 *******************************************************************************/

#include "LCD5110.h"
#include "Pixel_EN.h"
#include "string.h"
#include "zf_common_headfile.h"
//#include "Pixel_CH.h"
static uint8_t lcd_buf[84*6] ;

/*******************************************************************************
* Function Name  : LCD_Init
* Description    : LCD初始化
* Input          : None	
* Output         : None
* Return         : None
*******************************************************************************/
void LCD5110_Init(void)
{
	  LCD5110_IO_Configuration();
	  //复位LCD_低电平脉冲
	  LCD_RST_L();		
	  delay_ms(5);
   	LCD_RST_H();
	  //复位串行接口_高电平脉冲
	  LCD_CE_H(); 
	  delay_ms(5);
	  LCD_CE_L(); 
	  //设置LCD
    LCD_Send(0x21, DC_CMD);	//使用扩展命令设置LCD模式
    LCD_Send(0xC8, DC_CMD);	//设置偏置电压
    LCD_Send(0x06, DC_CMD);	//温度校正
    LCD_Send(0x13, DC_CMD); //1:48
    LCD_Send(0x20, DC_CMD);	//使用基本命令
    LCD_Send(0x0C, DC_CMD);	//设定显示模式，反转显示
}
/*******************************************************************************
* Function Name  : LCD_SetContrast
* Description    : 设置LCD对比度(对比度范围: 0~127)
* Input          : uint8_t contrast
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetContrast(uint8_t contrast)
{
    LCD_Send(0x21, DC_CMD);
    LCD_Send(0x80 | contrast, DC_CMD);
    LCD_Send(0x20, DC_CMD);
}
/*******************************************************************************
* Function Name  : LCD_SetXY
* Description    : 设置LCD当前坐标		//与原代码修改，横纵坐标设置变换
* Input          : uint8_t X, uint8_t Y	
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetXY(uint8_t Y, uint8_t X)
{
	if (X>13) X = 13;
	if (Y>5) Y = 5;
	X *= 6;
	//Y *= 8;
	LCD_Send(0x80 | X, DC_CMD);    // 列 
	delay_ms(10)         ;  
	LCD_Send(0x40 | Y, DC_CMD);    // 行
}
/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : LCD清屏
* Input          : None	
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Clear(void)
{
	uint16_t i;
  LCD_Send(0x80, DC_CMD);
	delay_ms(5);
	LCD_Send(0x40, DC_CMD);
	for(i=0; i<504; i++)
	LCD_Send(0, DC_DATA);	  
}
/*******************************************************************************
* Function Name  : LCD_Send
* Description    : 向LCD发送数据
* Input          : uint8_t data, DCType dc
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Send(uint8_t data, DCType dc)
{
	uint8_t i=8;
	
   	if (dc==DC_CMD)
		LCD_DC_CMD();	//发送命令
	else
		LCD_DC_DATA();//发送数据
	while (i--)
	{
		LCD_CLK_L();
		if(data&0x80)
			LCD_MOSI_H();	/* MSB first */
		else 
			LCD_MOSI_L();
		LCD_CLK_H();
		data <<= 1;		/* Data shift */
	}

}
/*******************************************************************************
* Function Name  : LCD_Write_Char
* Description    : 向LCD写一个英文字符
* Input          : uint8_t ascii
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Write_Char(uint8_t ascii)
{
    uint8_t n;
    ascii -= 32; //ASCII码-32
    for (n=0; n<6; n++)
		LCD_Send(Font6x8[ascii][n], DC_DATA);
}
/*******************************************************************************
* Function Name  : LCD_Write_Hanzi
* Description    : 向LCD写一个汉字
* Input          : uint8_t ascii
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Write_Hanzi(uint8_t X, uint8_t Y,uint8_t GBK)
{
    uint8_t n;
     LCD_SetXY(X,Y); 
     for (n=0; n<12; n++)
	      {      
		           LCD_Send(Font12x16_chinese[GBK][n], DC_DATA);
		    }
	 
	  delay_ms(10);
		LCD_SetXY(X,Y+1); 
    for (n=12; n<24; n++)
	    {      
		         LCD_Send(Font12x16_chinese[GBK][n], DC_DATA);
		  }
			
}
/*******************************************************************************
* Function Name  : LCD_Write_EnStr
* Description    : 向LCD写英文字符串
* Input          : uint8_t ascii
* Output         : None
* Return         : None
*******************************************************************************/
//void LCD_Write_EnStr(uint8_t X, uint8_t Y, uint8_t* s)
void LCD_Write_EnStr(uint8_t X, uint8_t Y, char* s)
{
//    uint8_t * str = s;	//强转警告
		char * str = s;
    int i = 0;
    int lcd_index =0;
		printf("get in");
    if(str == 0 )
    {
        return ;
    }

    LCD_SetXY(X,Y);
    while(*str)
    {
        //拷贝显示数据到缓冲区
        for(i=0;i<6;i++)
        {
            lcd_buf[lcd_index ++ ] = Font6x8[*str - 32][i];
        }
					//memcpy(lcd_buf+6*str,&Font6x8[*str - 32][0],6);	
        str ++ ;
    }
    lcd_buf[lcd_index ++ ] = 0 ; // lcd_index ++ 多发送一个0否者最后一个字符会缺少一个像素

    for(i = 0 ;i<lcd_index ;i++)
    {
        LCD_Send(lcd_buf[i], DC_DATA);
    }
   
}

/**
*   @FuncName   LCD_Write_FloatNum
*   @brief  显示浮点数
*   @param  x:横坐标，y:纵坐标，S:显示浮点数
*   @return none
*/
void LCD_Write_FloatNum(uint8_t X, uint8_t Y, float s)
{
	char aa[10];

	sprintf(aa,"%5.2f",s);//浮点型数据转为指定格式的字符串
	LCD_Write_EnStr(X,Y,aa); //直接送字符显示函数

}

void LCD_Write_IntNum(uint8_t X, uint8_t Y, int s)
{
	char aa[10];

	sprintf(aa,"%d",s);//浮点型数据转为指定格式的字符串
	LCD_Write_EnStr(X,Y,aa); //直接送字符显示函数

}





/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD5110_IO_Configuration(void)
{  	 
//	GPIO_Init_Type GPIO_InitStructure;
//	/*LCD5110_LCD_CTRL_PORT*/
// 	GPIO_InitStructure.Pins =LCD_RST|LCD_CE|LCD_DC|LCD_CLK|LCD_MOSI	;
// 	GPIO_InitStructure.Speed = GPIO_Speed_50MHz;
// 	GPIO_InitStructure.PinMode = GPIO_PinMode_Out_PushPull;	//通用推挽输出
// 	GPIO_Init(LCD_CTRL_PORT, &GPIO_InitStructure);
  /*config spi1 ,clk mosi */
	gpio_init(D7, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // 初始化 LED1 输出 默认高电平 推挽输出模式
	gpio_init(D5, GPO, GPIO_HIGH, GPO_PUSH_PULL); 
	gpio_init(D14, GPO, GPIO_HIGH, GPO_PUSH_PULL); 
	gpio_init(D4, GPO, GPIO_HIGH, GPO_PUSH_PULL); 
	gpio_init(D6, GPO, GPIO_HIGH, GPO_PUSH_PULL); 
}



