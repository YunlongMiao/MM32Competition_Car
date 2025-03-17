#include "motor.h"
#include "zf_common_headfile.h"



void Motor_IO_Init();
void Motor_Pwm_Init();
void Encoder_Init();



//-------------------------------------------------------------------------------------------------------------------
// 函数简介   电机初始化函数，内含编码器，PWM初始化  
// 参数说明     
// 参数说明    
// 返回参数    
// 使用示例     
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void Motor_Init(){
	
	Motor_IO_Init();	//电机IO初始化
	Motor_Pwm_Init();	//PWM初始化
	Encoder_Init();		//编码器初始化
}



//-------------------------------------------------------------------------------------------------------------------
// 函数简介 电机IO初始化    
// 参数说明  void   
// 参数说明    
// 返回参数    
// 使用示例     
// 备注信息  初始化引脚不可多个一起设置，分开设置   
//-------------------------------------------------------------------------------------------------------------------
void Motor_IO_Init(){
	gpio_init(A4, GPO, GPIO_LOW, GPO_PUSH_PULL);// 初始化 LED1 输出 默认高电平 推挽输出模式
	gpio_init(A5, GPO, GPIO_LOW, GPO_PUSH_PULL);
	gpio_init(A6, GPO, GPIO_LOW, GPO_PUSH_PULL);
	gpio_init(A7, GPO, GPIO_LOW, GPO_PUSH_PULL);
}




//-------------------------------------------------------------------------------------------------------------------
// 函数简介    编码器初始化 
// 参数说明    定时器
// 参数说明    编码器通道AB
// 返回参数    
// 使用示例     
// 备注信息    逐飞编码器驱动定义zf_driver_encoder 
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Init(){

	//编码器1：定时器3-CH12-B4、5
	encoder_quad_init(TIM3_ENCODER,TIM3_ENCODER_CH1_B4,TIM3_ENCODER_CH2_B5);	
	//编码器2：定时器4-CH12-D12、13
	encoder_quad_init(TIM4_ENCODER,TIM4_ENCODER_CH1_D12,TIM4_ENCODER_CH2_D13);
	
	
	//ENCODER 接口获取编码器计数-encoder_get_count(TIM3_ENCODER);
	//int16   encoder_get_count       (encoder_index_enum encoder_n);
	//ENCODER 清空编码器计数-encoder_clear_count(TIM3_ENCODER);
	//void    encoder_clear_count     (encoder_index_enum encoder_n);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM初始化
// 参数说明     定时器通道引脚代号
// 参数说明    	PWM频率，占空比
// 返回参数    
// 使用示例     
// 备注信息     zf_driver_pwm
//-------------------------------------------------------------------------------------------------------------------
//void Motor_Pwm_Init(uint32 frep){
void Motor_Pwm_Init(){

	//当前工程PWM频率-100HZ
	//定时器5-CH1—PWM
	pwm_init(TIM5_PWM_CH1_A0,120,0);	//通道，频率(HZ)，占空比 满值12500
	//定时器5-CH2—PWM
	pwm_init(TIM5_PWM_CH2_A1,120,0);	//通道，频率(HZ)，占空比
	
	
	//PWM 更新占空比-pwm_set_duty(TIM5_PWMCH1_A0, PWM_DUTY_MAX / 4);
	//void    pwm_set_duty    (pwm_channel_enum pin, const uint32 duty);

}




/**
*   @FuncName   Left_Direction
*   @brief  左侧电机正反转
*   @param  none
*   @return none
*/
void Left_Direction(bool direction){
	if(direction){
		gpio_set_level(A4,0);
		gpio_set_level(A5,1);
	}else{
		gpio_set_level(A4,1);
		gpio_set_level(A5,0);
	}
}

/**
*   @FuncName   Right_Direction
*   @brief  右侧电机正反转
*   @param  none
*   @return none
*/
void Right_Direction(bool direction){
	if(direction){
		gpio_set_level(A6,1);
		gpio_set_level(A7,0);
	}else{
		gpio_set_level(A6,0);
		gpio_set_level(A7,1);
	}
}

/**
*   @FuncName   Motor_Stop
*   @brief  电机刹车
*   @param  none
*   @return none
*/

void Motor_Stop(){
		gpio_set_level(A4,1);
		gpio_set_level(A5,1);
		gpio_set_level(A6,1);
		gpio_set_level(A7,1);
}

