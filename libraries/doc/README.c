#include "readme.h"

#if EN_MORE
#include "zf_common_headfile.h"

#include "motor_control.h"
#include "motor.h"

#define PIT_Motor                         (TIM7_PIT ) // ʹ�õ������жϱ�� ����޸� ��Ҫͬ����Ӧ�޸������жϱ���� isr.c �еĵ���
extern uint8 Gray_Num[8];
int test = 0;

int main(){
	
	key_state_enum flag1;
	uint8 data[64]; 
	uint32 len;
	
  clock_init(SYSTEM_CLOCK_120M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
  debug_init();
	gpio_init(H2, GPO, GPIO_LOW, GPO_PUSH_PULL);
	Motor_Control_Init();
//	key_init(10);	//ɨ������10MS 
//	pit_ms_init(PIT_Motor,10);
//	printf("%d",0);
	while(1){
//		key_scanner();
//		flag1 = key_get_state(KEY_1);
		gpio_toggle_level(H2);
		len = debug_read_ring_buffer(data);
		if(len != 1)
			if(data[0] == 5){
			gpio_set_level(E9, GPIO_HIGH);                                            // BEEP ��
			system_delay_ms(100);
			gpio_set_level(E9, GPIO_LOW); 
			}
			printf("%d\r\n",data[0]);

//			if(test < 32000){
//				test += 500;
//				Left_Direction(true);
//				Right_Direction(true);
//				pwm_set_duty(TIM5_PWM_CH1_A0,test);
//				pwm_set_duty(TIM5_PWM_CH2_A1,test);
//			}
//			else
//				test = 0;
		delay_ms(1500);
	}
}

void Motor_pit_handler (void)
{
//	SETPWM(test);
//	printf("\r\nEncouder1=%d:",Read_Encoder1());
//	printf("\r\nEncouder2=%d:",Read_Encoder2());
//	printf("\r\npwm=%d",test);
		Gray_Control();
}
#endif



#if EN_MROE
#include "zf_common_headfile.h"
#include "ADC_USE.h"
#include "motor_control.h"
#include "Sensing_Control.h"
#include "esp8266.h"

#define PIT_Motor                         (TIM7_PIT ) // ʹ�õ������жϱ�� ����޸� ��Ҫͬ����Ӧ�޸������жϱ���� isr.c �еĵ���


int main(){
	uint8 data[64]; 
	uint32 len;
	Control_Data_TypeDef Control_Data;
	
  clock_init(SYSTEM_CLOCK_120M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
  debug_init();
	Sensing_Control_Init();
//	pit_ms_init(PIT_Motor,10);
	gpio_init(H2, GPO, GPIO_LOW, GPO_PUSH_PULL);
	delay_ms(1000);
	while(1){
		
		gpio_toggle_level(H2);
		
//		len = debug_read_ring_buffer(data);
//		if(len != 1)
//			if(data[0] == 5){
//			gpio_set_level(E9, GPIO_HIGH);                                            // BEEP ��
//			system_delay_ms(100);
//			gpio_set_level(E9, GPIO_LOW); 
//			}
//			
//			printf("%d\r\n",data[0]);
			Get_Sensing();

//		Get_All_Sensing(&Control_Data);
//		
//		printf("ADC_power=%f\r\n",Control_Data.power);
//		printf("ADC_PM2_5=%f\r\n",Control_Data.pm2_5);
//		printf("Tem=%f\r\n",Control_Data.Tem);
//		printf("Sound=%f\r\n",Control_Data.Sound);
//		printf("Co=%f\r\n",Control_Data.Co);
//		printf("Humi=%f\r\n",Control_Data.ShiDu);
//		printf("fire=%d\r\n",Control_Data.fire);
		delay_ms(1500);

	}
}

void GET_pit_handler (void)
{
	uint8 data[64]; 
	uint32 len;
	
	len = debug_read_ring_buffer(data);
	if(len != 0)
	{
		printf("len = %d\r\n",len);
		printf("data[0] = %d\r\n",data[0]);
		printf("data[1] = %d\r\n",data[1]);
		printf("data[2] = %d\r\n",data[2]);
		if(data[0] == 11)	//�ϴ�������Ϣ
		{
			printf("data[0] = %d\r\n",data[0]);
				//Get_Sensing();
			
		}
		else if(data[0] == 22)//С��������Ϣ
		{
			printf("data[0] = %d\r\n",data[0]);
			printf("data[1] = %d\r\n",data[1]);
//				switch(data[1]){
//						
//				}
				
		}
		else if(data[0] == 33)	//������Ϣ�·�
		{
				printf("data[0] = %d\r\n",data[0]);
		}
	}
//	printf("NONE\r\n");
}


#endif



#if EN_IMU963
	
#include "zf_common_headfile.h"
#include "LCD5110.h"
#define LED1                        (H2 )

#define PIT                         (TIM6_PIT )                                 // ʹ�õ������жϱ�� ����޸� ��Ҫͬ����Ӧ�޸������жϱ���� isr.c �еĵ���

int main (void)
{
    clock_init(SYSTEM_CLOCK_120M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART
		LCD5110_Init();
    // �˴���д�û����� ���������ʼ�������
    gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // ��ʼ�� LED1 ��� Ĭ�ϸߵ�ƽ �������ģʽ
		delay_ms(10);         
		LCD_Clear();
	

    while(1)
    {
        if(imu963ra_init())
        {
            LCD_Write_EnStr(0,1,"IMU963RA init error.");                                 // IMU963RA ��ʼ��ʧ��
        }
        else
        {
            break;
        }
        gpio_toggle_level(LED1);                                                // ��ת LED ���������ƽ ���� LED ���� ��ʼ����������ƻ����ĺ���
    }
		pit_ms_init(PIT, 5);	//5ms����һ�ζ�ʱ��TIM6�жϻ�ȡ����������
    // �˴���д�û����� ���������ʼ�������

    while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
				printf("\r\nIMU963RA  acc  data: x=%5d, y=%5d, z=%5d\r\n", imu963ra_acc_x, imu963ra_acc_y, imu963ra_acc_z);
        printf("\r\nIMU963RA  gyro data: x=%5d, y=%5d, z=%5d\r\n", imu963ra_gyro_x, imu963ra_gyro_y, imu963ra_gyro_z);
        printf("\r\nIMU963RA  mag  data: x=%5d, y=%5d, z=%5d\r\n\n\n\n\n", imu963ra_mag_x, imu963ra_mag_y, imu963ra_mag_z);
			
        printf("\r\nIMU963RA  acc data(g/s^2): x=%5f, y=%5f, z=%5f\r\n", imu963ra_acc_f_x, imu963ra_acc_f_y, imu963ra_acc_f_z);
        printf("\r\nIMU963RA  gyro data(��/s): x=%5f, y=%5f, z=%5f\r\n", imu963ra_gyro_f_x, imu963ra_gyro_f_y, imu963ra_gyro_f_z);
        printf("\r\nIMU963RA  mag     data(G): x=%5f, y=%5f, z=%5f\r\n\n\n\n\n", imu963ra_mag_f_x, imu963ra_mag_f_y, imu963ra_mag_f_z);
        
			
			gpio_toggle_level(LED1);                                                // ��ת LED ���������ƽ ���� LED ����
        system_delay_ms(1000);
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     PIT ���жϴ����� ����������� PIT ��Ӧ�Ķ�ʱ���жϵ��� ��� isr.c
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     pit_handler();
//-------------------------------------------------------------------------------------------------------------------
void pit_handler (void)
{
    imu963ra_get_acc();                                                         // ��ȡ IMU963RA �ļ��ٶȲ�����ֵ
    imu963ra_get_gyro();                                                        // ��ȡ IMU963RA �Ľ��ٶȲ�����ֵ
    imu963ra_get_mag();                                                         // ��ȡ IMU963RA �ĵشżƲ�����ֵ
}

#endif





/**
*   @FuncName   mpu6050��������
*   @brief  something
*   @param  none
*   @return none
*/

#if EN_MPU6050
/*
 * Macros.
 */

#define APP_MPU6050_WAIT_TIME 1000u

/*
 * Variables.
 */

float app_mpu6050_g[3u];    /* save mpu6050 acceleration data. */
float app_mpu6050_dps[3u];  /* save mpu6050 angular gyro data. */
float app_mpu6050_d;        /* save mpu6050 temperature data. */

/*
 * Declerations.
 */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
		printf("6050 demo.\r\n");

    printf("libdriver_mpu6050_basic demo.\r\n");

    /* init */
    while(mpu6050_basic_init(BOARD_MPU6050_ADDR) != 0u)
    {
        mpu6050_interface_debug_print("mpu6050: mpu6050 init faild.\r\n");
        mpu6050_interface_delay_ms(APP_MPU6050_WAIT_TIME);
    }

    while(1)
    {
        /* read. */
        mpu6050_basic_read(app_mpu6050_g, app_mpu6050_dps);
        mpu6050_basic_read_temperature(&app_mpu6050_d);

        /* output. */
        mpu6050_interface_debug_print("mpu6050: acc x is %0.2fg.\r\n", (double)app_mpu6050_g[0]);
        mpu6050_interface_debug_print("mpu6050: acc y is %0.2fg.\r\n", (double)app_mpu6050_g[1]);
        mpu6050_interface_debug_print("mpu6050: acc z is %0.2fg.\r\n", (double)app_mpu6050_g[2]);
        mpu6050_interface_debug_print("mpu6050: gyro x is %0.2fdps.\r\n", (double)app_mpu6050_dps[0]);
        mpu6050_interface_debug_print("mpu6050: gyro y is %0.2fdps.\r\n", (double)app_mpu6050_dps[1]);
        mpu6050_interface_debug_print("mpu6050: gyro z is %0.2fdps.\r\n", (double)app_mpu6050_dps[2]);
        mpu6050_interface_debug_print("mpu6050: temperature %0.2fC.\r\n", (double)app_mpu6050_d);

        /* delay. */
        mpu6050_interface_delay_ms(APP_MPU6050_WAIT_TIME);

    }

}

/* EOF. */

#endif





/**
*   @FuncName   encoder ��������
*   @brief  ��������������
*   @param  none
*   @return none
*/

#if EN_ENCODER

#include "board_init.h"
#include "driver_mpu6050_basic.h"

#include "board_init.h"
#include "encoder.h" 

#define APP_TIM_UPDATE_PERIOD  2000u

void Encoder_Tim_Init(void);
void app_delay(uint32_t t);

uint32_t app_tim_counter_val = 0u;
TIM_EncoderDirection_Type app_tim_encoder_dir = TIM_EncoderDirection_Backward;

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("\r\ntim_slave_mode_encoder.\r\n");

    Encoder_Tim_Init();	//��������ʼ��
    
    while (1)
    {

        getchar();
        if ( ( app_tim_encoder_dir = TIM_GetEncoder(TIM_3, &app_tim_counter_val) ) == TIM_EncoderDirection_Forward )	//��������ת�����ȡ����תΪ1������ȡ��������ֵ
        {
            printf("���������ǰ:%u.\r\n", (unsigned)app_tim_counter_val);
        }
        else
        {
            printf("���������ǰ:%u.\r\n\r\n\r\n", (unsigned)app_tim_counter_val);
        }
				if ( ( app_tim_encoder_dir = TIM_GetEncoder(TIM_4, &app_tim_counter_val) ) == TIM_EncoderDirection_Forward )	//��������ת�����ȡ����תΪ1������ȡ��������ֵ
        {
            printf("�ұ�������ǰ:%u.\r\n", (unsigned)app_tim_counter_val);
        }
        else
        {
            printf("�ұ�������ǰ:%u.\r\n", (unsigned)app_tim_counter_val);
        }
				printf("\r\n\n\n\n");
    }
}





/* Use cpu running here for delay. */
void app_delay(uint32_t t)
{
    for (uint32_t i = 0u; i < t; i++)
    {
        for (uint32_t j = 0u; j < 1000u; j++)
        {
            __NOP();
        }
    }
}


#endif




#if EN_TIM5_PWM	//PWM�����ʱ��5

#include "board_init.h"
#include "driver_mpu6050_basic.h"

#include "board_init.h"
#include "encoder.h"
#include "pwm.h"


#define APP_TIM_UPDATE_PERIOD  1000u    /* 1ms period, scale. */

#define APP_TIM_PWM_NUM   8u
uint16_t app_tim_pwm_val[APP_TIM_PWM_NUM] =
{
    (APP_TIM_UPDATE_PERIOD >> 3u) * 1u, /* 1/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 2u, /* 2/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 3u, /* 3/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 4u, /* 4/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 5u, /* 5/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 6u, /* 6/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 7u, /* 7/8. */
    APP_TIM_UPDATE_PERIOD,              /* 8/8. */
};


/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("\r\ntim_comp_output_compare_pwm.\r\n");

    /* Setup the timer. */
    Tim_Pwm_Init();

    while (1)
    {
        for (uint32_t i = 0; i < 8u; i++)
        {
            getchar();
            TIM_PutChannelValue(TIM_5, TIM_CHN_1, app_tim_pwm_val[i]);/* Change duty cycle. */
						TIM_PutChannelValue(TIM_5, TIM_CHN_2, app_tim_pwm_val[i]);/* Change duty cycle. */
						TIM_PutChannelValue(TIM_5, TIM_CHN_3, app_tim_pwm_val[i]);/* Change duty cycle. */
						TIM_PutChannelValue(TIM_5, TIM_CHN_4, app_tim_pwm_val[i]);/* Change duty cycle. */
            printf("PWM value: %u\r\n", (unsigned)app_tim_pwm_val[i]);
        }
    }
}
#endif



#if EN_LED

#include "board_init.h"
#include "driver_mpu6050_basic.h"

#include "board_init.h"
#include "encoder.h"
#include "pwm.h"
#include "led.h"

int main(){

	BOARD_Init();
	
	while(1){
	
//		Light();
	GPIO_SetBits(GPIOF,GPIO_PIN_5);	//LED2��
	delay_us(10000);
	GPIO_ClearBits(GPIOF,GPIO_PIN_5);	//LED2��
	delay_us(10000);
		
	}
}

#endif



#if EN_LCD5110
#include "board_init.h" 
#include "LCD5110.h" 

int main(void)
{
  BOARD_Init();
	LCD5110_Init();
	delay_ms(10);         
	LCD_Clear();
	 
	while(1){
	printf("start");
	 delay_ms(10); 
	LCD_Write_EnStr(0,0,"**************");
//	LCD_Write_EnStr(1,0,"gu dong dong");
//	LCD_Write_EnStr(2,0,"smart health");
//	LCD_Write_EnStr(3,0,"JiangsuZhihai");	
//	LCD_Write_EnStr(4,0,"ElectronicTechnology");
//	LCD_Write_EnStr(5,0,"***123.*******");
		LCD_SetXY(1,0);
		LCD_Write_Char('A');
		LCD_Write_Hanzi(2,0,1);
		LCD_Write_EnStr(3,0,"3.775");
		LCD_Write_FloatNum(4,0,3.775);
	}
}

#endif


#if EN_POWER
#include "zf_common_headfile.h"



// **************************** �������� ****************************
int main (void)
{
    clock_init(SYSTEM_CLOCK_120M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART

    // �˴���д�û����� ���������ʼ�������
    uint16 voltage_adc = 0;
    float voltage_now = 0;
    adc_init(ADC2_CH14_C4, ADC_12BIT);                                          // �����Ŵ������� ADC1 ��ؼ���� ADC2
    printf("\r\nBattery voltage detection demo.");
    // �˴���д�û����� ���������ʼ�������

    while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        voltage_adc = adc_convert(ADC2_CH14_C4);
        voltage_now = 13.2 * voltage_adc / 4096;                                // ������ɿƼ�ѧϰ�����ѹ���� ���Ӧ���ǵ�ص�ѹ 1/4 ��ô������� 13.2V
        printf("\r\nBattery voltage is : %d. (0-4096)", voltage_adc);           // ���ڵ��������� ADC��Ȿ��Ҳ����һЩ��� ���������Ӧ��ֵ���ܸ�ʵ�ʵ�ѹ�н϶����
        printf("\r\nBattery voltage is : %2.3f. (0V-13.2V)", voltage_now);      // ���ﻻ���һ�����ʵ�ʵ�ص�ѹ����� ��Ҫ����ʵ�ʵļ����Ϊ׼ �������н���
        system_delay_ms(3000);
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

#endif

#if EN_FIRE
#include "board_init.h"
#include "LCD5110.h" 

int main()
{
	bool FLAG;
	BOARD_Init();
	LCD5110_Init();
	delay_ms(10);         
	LCD_Clear();
	
	while(1){
		LCD_Write_EnStr(0,1,"START");
		FLAG = GPIO_ReadInDataBit(GPIOA,15);
		if(FLAG){
			LCD_Write_EnStr(1,1,"fire:ture");
			printf("fire:ture\n");
		}
		else{
			LCD_Write_EnStr(1,1,"fire:flase");
			printf("fire:flase\n");
		}
		delay_ms(1000);
	}
}
#endif

#if EN_PM25
#include "board_init.h" 
#include "LCD5110.h" 
#include "ADC_USE.h"
#include "stdio.h"

int main (void)
{
  BOARD_Init();
	ADC_Use_Init();
	LCD5110_Init();
	delay_ms(10);         
	LCD_Clear();


    float voltage_now = 0;
		float pm25_now = 0;


    while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        
        voltage_now = ADC_POWER();                                // ������ɿƼ�ѧϰ�����ѹ���� ���Ӧ���ǵ�ص�ѹ 1/4 ��ô������� 13.2V
				pm25_now = ADC_PM25_Init();
//				pm25_now = ADC_PM25();
				LCD_Write_EnStr(2,0,"POW:");
				LCD_Write_FloatNum(2,4,voltage_now);

				LCD_Write_EnStr(4,0,"TEX:");
				LCD_Write_FloatNum(4,4,pm25_now);
				if (pm25_now<0)
					pm25_now=0;            //��λ//
				if (pm25_now>500)        
					pm25_now=500;

     printf("\r\n:%fug/m3\n\r",pm25_now);
        delay_ms(3000);
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}
#endif


#if EN_DHT11
#include "board_init.h" 
#include "LCD5110.h" 
#include "ADC_USE.h"
#include "stdio.h"
#include "dht11.h"

int main (void)
{
	char str[] = "";
	DHT11_Data_TypeDef DHT11_Data;
	
  BOARD_Init();
	LCD5110_Init();
	delay_ms(10);         
	LCD_Clear();




    while(1)
    {
				if( Read_DHT11(&DHT11_Data)==1)
			{

//				sprintf((char*)str, "%10d.%10d �� ",DHT11_Data.temp_int,DHT11_Data.temp_deci);
				LCD_Write_IntNum(1,0,DHT11_Data.temp_int);
				LCD_Write_EnStr(1,2,".");
				LCD_Write_IntNum(1,3,DHT11_Data.temp_deci);
				printf("%d.%d C\n",DHT11_Data.temp_int,DHT11_Data.temp_deci);
//				sprintf((char*)str, "%10d.%10d",DHT11_Data.humi_int,DHT11_Data.humi_deci);
				LCD_Write_IntNum(2,0,DHT11_Data.humi_int);
				LCD_Write_EnStr(2,2,".");
				LCD_Write_IntNum(2,3,DHT11_Data.humi_deci);
				printf("%d.%d C\n",DHT11_Data.humi_int,DHT11_Data.humi_deci);
			}
			else
			{
				printf("Read DHT11 ERROR!\r\n");//��ȡ����ʧ�ܣ����ڴ�ӡ��Read DHT11 ERROR.
			}
    }
}

#endif
