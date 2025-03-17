
/*******************************************************************************
 ************************* QQ858860583 *****************************************
 ************************* ����ԭ����̳�ţ�cornrn ******************************	
 *******************************************************************************/

#include "LCD5110.h"
#include "Pixel_EN.h"
#include "string.h"
#include "zf_common_headfile.h"
//#include "Pixel_CH.h"
static uint8_t lcd_buf[84*6] ;

/*******************************************************************************
* Function Name  : LCD_Init
* Description    : LCD��ʼ��
* Input          : None	
* Output         : None
* Return         : None
*******************************************************************************/
void LCD5110_Init(void)
{
	  LCD5110_IO_Configuration();
	  //��λLCD_�͵�ƽ����
	  LCD_RST_L();		
	  delay_ms(5);
   	LCD_RST_H();
	  //��λ���нӿ�_�ߵ�ƽ����
	  LCD_CE_H(); 
	  delay_ms(5);
	  LCD_CE_L(); 
	  //����LCD
    LCD_Send(0x21, DC_CMD);	//ʹ����չ��������LCDģʽ
    LCD_Send(0xC8, DC_CMD);	//����ƫ�õ�ѹ
    LCD_Send(0x06, DC_CMD);	//�¶�У��
    LCD_Send(0x13, DC_CMD); //1:48
    LCD_Send(0x20, DC_CMD);	//ʹ�û�������
    LCD_Send(0x0C, DC_CMD);	//�趨��ʾģʽ����ת��ʾ
}
/*******************************************************************************
* Function Name  : LCD_SetContrast
* Description    : ����LCD�Աȶ�(�Աȶȷ�Χ: 0~127)
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
* Description    : ����LCD��ǰ����		//��ԭ�����޸ģ������������ñ任
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
	LCD_Send(0x80 | X, DC_CMD);    // �� 
	delay_ms(10)         ;  
	LCD_Send(0x40 | Y, DC_CMD);    // ��
}
/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : LCD����
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
* Description    : ��LCD��������
* Input          : uint8_t data, DCType dc
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Send(uint8_t data, DCType dc)
{
	uint8_t i=8;
	
   	if (dc==DC_CMD)
		LCD_DC_CMD();	//��������
	else
		LCD_DC_DATA();//��������
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
* Description    : ��LCDдһ��Ӣ���ַ�
* Input          : uint8_t ascii
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Write_Char(uint8_t ascii)
{
    uint8_t n;
    ascii -= 32; //ASCII��-32
    for (n=0; n<6; n++)
		LCD_Send(Font6x8[ascii][n], DC_DATA);
}
/*******************************************************************************
* Function Name  : LCD_Write_Hanzi
* Description    : ��LCDдһ������
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
* Description    : ��LCDдӢ���ַ���
* Input          : uint8_t ascii
* Output         : None
* Return         : None
*******************************************************************************/
//void LCD_Write_EnStr(uint8_t X, uint8_t Y, uint8_t* s)
void LCD_Write_EnStr(uint8_t X, uint8_t Y, char* s)
{
//    uint8_t * str = s;	//ǿת����
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
        //������ʾ���ݵ�������
        for(i=0;i<6;i++)
        {
            lcd_buf[lcd_index ++ ] = Font6x8[*str - 32][i];
        }
					//memcpy(lcd_buf+6*str,&Font6x8[*str - 32][0],6);	
        str ++ ;
    }
    lcd_buf[lcd_index ++ ] = 0 ; // lcd_index ++ �෢��һ��0�������һ���ַ���ȱ��һ������

    for(i = 0 ;i<lcd_index ;i++)
    {
        LCD_Send(lcd_buf[i], DC_DATA);
    }
   
}

/**
*   @FuncName   LCD_Write_FloatNum
*   @brief  ��ʾ������
*   @param  x:�����꣬y:�����꣬S:��ʾ������
*   @return none
*/
void LCD_Write_FloatNum(uint8_t X, uint8_t Y, float s)
{
	char aa[10];

	sprintf(aa,"%5.2f",s);//����������תΪָ����ʽ���ַ���
	LCD_Write_EnStr(X,Y,aa); //ֱ�����ַ���ʾ����

}

void LCD_Write_IntNum(uint8_t X, uint8_t Y, int s)
{
	char aa[10];

	sprintf(aa,"%d",s);//����������תΪָ����ʽ���ַ���
	LCD_Write_EnStr(X,Y,aa); //ֱ�����ַ���ʾ����

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
// 	GPIO_InitStructure.PinMode = GPIO_PinMode_Out_PushPull;	//ͨ���������
// 	GPIO_Init(LCD_CTRL_PORT, &GPIO_InitStructure);
  /*config spi1 ,clk mosi */
	gpio_init(D7, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // ��ʼ�� LED1 ��� Ĭ�ϸߵ�ƽ �������ģʽ
	gpio_init(D5, GPO, GPIO_HIGH, GPO_PUSH_PULL); 
	gpio_init(D14, GPO, GPIO_HIGH, GPO_PUSH_PULL); 
	gpio_init(D4, GPO, GPIO_HIGH, GPO_PUSH_PULL); 
	gpio_init(D6, GPO, GPIO_HIGH, GPO_PUSH_PULL); 
}



