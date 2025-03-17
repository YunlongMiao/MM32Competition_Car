#include "motor_control.h"
#include "motor.h"
#include "GraySensor.h"
#include "LCD5110.h"
#include "pid.h"

uint8 Gray_Num[8];

bool Left_flag  = false,
		 Right_flag = false;



void Motor_Control_Init(){
	Motor_Init();
	gw_gray_init();	//灰度传感器
	LCD5110_Init();
	delay_ms(10);         
	LCD_Clear();
}





//8 4 2 1

uint8 Num_Exchange_4(uint8 binary_num){

	unsigned int swapped_binary_num;
	
	swapped_binary_num = ((binary_num & 0b0001) << 3) | ((binary_num & 0b0010) << 1) | ((binary_num & 0b0100) >> 1) | ((binary_num & 0b1000) >> 3);
	return swapped_binary_num;
}




int Gray_Judge()
{
	float error;
	int temp = 0,left = 0,right = 0;
	uint8 last = 0,left_T = 0,temp_T = 0;
	
	
	temp_T = gw_gray_serial_read();
	
	left_T = Num_Exchange_4( (temp_T & 0xf) );		//8 1  4 2
	left = 0 - left_T;				//-8 -4 -2 -1
	right = temp_T >> 4;			// 1  2  4  8 
	temp = left + right;
//	printf("\ntemp=%d",temp);
	if( (temp == 0) && (temp_T == 0xe7) )
		return 0;
	else if(temp < 0){
				if(-15<= temp && temp< -7)
					return -4;
				else if(-7<= temp && temp< -3)
					return -3;
				else if(-3<= temp && temp< -1)
					return -2;
				else if(-1<= temp && temp< 0)
					return -1;
	}else{
			if(15>= temp && temp > 7)
					return 4;
			else if( 7>= temp && temp > 3)
					return 3;
			else if( 3>= temp && temp > 1)
					return 2;
			else if( -1>= temp && temp > 0)
					return 1;
			else if(temp == 0)
				return 0;
		}
	return 0;

}


float Get_True(float num){

	if(num >= 0)
			return num;
	else
		return -num;
	
}



void Gray_Control(){
	static int Encoder_Value_L = 0,Encoder_Value_R = 0;
	int PWM_L = 0,PWM_R = 0;
	int Gray_Value = 0;
	float Gray_PID = 0;
	static int i = 0;
	
	Gray_Value = Gray_Judge();
	
	printf("%d\r\n",Gray_Value);
	
	if(Get_True(Gray_Value)<2)
	{
//		if(i<9){
//			Encoder_Value_L += Read_Encoder1() ;
//			Encoder_Value_R += Read_Encoder2() ;
//			i++;
//		}else{
//			i = 0;	
//			PWM_L = velocity_PID_value_L((Encoder_Value_L /10)*20 ) ;
//			PWM_R = velocity_PID_value_R((Encoder_Value_R /10)*25 ) ;

//			PWM_L = velocity_PID_value_L( ( (Encoder_Value_L +Encoder_Value_R)/10)*20 ) ;
//			printf("%d,%d,%d\n",PWM_L,PWM_R,500);

//			PWM_Xianfu(10000,&PWM_L);
//			PWM_Xianfu(10000,&PWM_L);
			SETPWM(500,TIM5_PWM_CH1_A0);
			SETPWM(500,TIM5_PWM_CH2_A1);
//			Encoder_Value_L = 0;
//			Encoder_Value_R = 0;	
//		}
		
	}else{
		
		if(i<9)
		{
			Encoder_Value_L += Read_Encoder1() ;
			Encoder_Value_R += Read_Encoder2() ;
			i++;
		}else{
			i = 0;	
			PWM_L =  - Gray_PID_value(Gray_Value) * 100;
			PWM_R =  + Gray_PID_value(Gray_Value) * 100;

			printf("%d,%d,%d\n",PWM_L,PWM_R,500);

			PWM_Xianfu(10000,&PWM_L);
			PWM_Xianfu(10000,&PWM_R);
			SETPWM(PWM_L,TIM5_PWM_CH1_A0);
			SETPWM(PWM_R,TIM5_PWM_CH2_A1);
//			Encoder_Value_L = 0;
//			Encoder_Value_R = 0;
			
		}
	
	}
}



//-------------------------------------------------------------------------------------------------------------------
// 函数简介  PWM限幅   
// 参数说明  最值   
// 参数说明    
// 返回参数    
// 使用示例     
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------

void PWM_Xianfu(int max,int *PWM)
{
	if(*PWM>max)  *PWM = max;
	if(*PWM<-max) *PWM =-max;
}


void SETPWM(int PWM,pwm_channel_enum PWM_CH_PIN)
{
	PWM = Get_True(PWM);
	if(PWM>0) //正转
	{
		Left_Direction(true);
		Right_Direction(true);
		pwm_set_duty(PWM_CH_PIN,3500+PWM);     
	}
	else      //反转
	{
		Left_Direction(false);
		Right_Direction(false);
		pwm_set_duty(PWM_CH_PIN,3500+(-PWM) );      
	}	
}




int Read_Encoder1(void)
{
	int speed;
	speed = (short)encoder_get_count(TIM3_ENCODER); //1.采集编码器的计数值并保存
	encoder_clear_count(TIM3_ENCODER);              //2.将定时器的计数值清零
	
	return speed;
}

int Read_Encoder2(void)
{
	int speed;
	speed = (short)encoder_get_count(TIM4_ENCODER); //1.采集编码器的计数值并保存
	encoder_clear_count(TIM4_ENCODER);              //2.将定时器的计数值清零
	
	return speed;
}
