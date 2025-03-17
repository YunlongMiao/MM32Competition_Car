#include "motor.h"
#include "zf_common_headfile.h"



void Motor_IO_Init();
void Motor_Pwm_Init();
void Encoder_Init();



//-------------------------------------------------------------------------------------------------------------------
// �������   �����ʼ���������ں���������PWM��ʼ��  
// ����˵��     
// ����˵��    
// ���ز���    
// ʹ��ʾ��     
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void Motor_Init(){
	
	Motor_IO_Init();	//���IO��ʼ��
	Motor_Pwm_Init();	//PWM��ʼ��
	Encoder_Init();		//��������ʼ��
}



//-------------------------------------------------------------------------------------------------------------------
// ������� ���IO��ʼ��    
// ����˵��  void   
// ����˵��    
// ���ز���    
// ʹ��ʾ��     
// ��ע��Ϣ  ��ʼ�����Ų��ɶ��һ�����ã��ֿ�����   
//-------------------------------------------------------------------------------------------------------------------
void Motor_IO_Init(){
	gpio_init(A4, GPO, GPIO_LOW, GPO_PUSH_PULL);// ��ʼ�� LED1 ��� Ĭ�ϸߵ�ƽ �������ģʽ
	gpio_init(A5, GPO, GPIO_LOW, GPO_PUSH_PULL);
	gpio_init(A6, GPO, GPIO_LOW, GPO_PUSH_PULL);
	gpio_init(A7, GPO, GPIO_LOW, GPO_PUSH_PULL);
}




//-------------------------------------------------------------------------------------------------------------------
// �������    ��������ʼ�� 
// ����˵��    ��ʱ��
// ����˵��    ������ͨ��AB
// ���ز���    
// ʹ��ʾ��     
// ��ע��Ϣ    ��ɱ�������������zf_driver_encoder 
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Init(){

	//������1����ʱ��3-CH12-B4��5
	encoder_quad_init(TIM3_ENCODER,TIM3_ENCODER_CH1_B4,TIM3_ENCODER_CH2_B5);	
	//������2����ʱ��4-CH12-D12��13
	encoder_quad_init(TIM4_ENCODER,TIM4_ENCODER_CH1_D12,TIM4_ENCODER_CH2_D13);
	
	
	//ENCODER �ӿڻ�ȡ����������-encoder_get_count(TIM3_ENCODER);
	//int16   encoder_get_count       (encoder_index_enum encoder_n);
	//ENCODER ��ձ���������-encoder_clear_count(TIM3_ENCODER);
	//void    encoder_clear_count     (encoder_index_enum encoder_n);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     PWM��ʼ��
// ����˵��     ��ʱ��ͨ�����Ŵ���
// ����˵��    	PWMƵ�ʣ�ռ�ձ�
// ���ز���    
// ʹ��ʾ��     
// ��ע��Ϣ     zf_driver_pwm
//-------------------------------------------------------------------------------------------------------------------
//void Motor_Pwm_Init(uint32 frep){
void Motor_Pwm_Init(){

	//��ǰ����PWMƵ��-100HZ
	//��ʱ��5-CH1��PWM
	pwm_init(TIM5_PWM_CH1_A0,120,0);	//ͨ����Ƶ��(HZ)��ռ�ձ� ��ֵ12500
	//��ʱ��5-CH2��PWM
	pwm_init(TIM5_PWM_CH2_A1,120,0);	//ͨ����Ƶ��(HZ)��ռ�ձ�
	
	
	//PWM ����ռ�ձ�-pwm_set_duty(TIM5_PWMCH1_A0, PWM_DUTY_MAX / 4);
	//void    pwm_set_duty    (pwm_channel_enum pin, const uint32 duty);

}




/**
*   @FuncName   Left_Direction
*   @brief  ���������ת
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
*   @brief  �Ҳ�������ת
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
*   @brief  ���ɲ��
*   @param  none
*   @return none
*/

void Motor_Stop(){
		gpio_set_level(A4,1);
		gpio_set_level(A5,1);
		gpio_set_level(A6,1);
		gpio_set_level(A7,1);
}

