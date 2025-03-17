#include "pid.h"

//速度环PI参数:
float VKp_L =  0.2,	
			VKi_L =  0.1,
			VKd_L =  0.3; 

//速度环PI参数:
float VKp_R =  0.3,	
			VKi_R =  0.125,
			VKd_R =  0.3; 

//extern float VKp,VKi;    //速度环参数
float velocity_Goal = 300.0;
float filt_velocity;     //滤波后的速度
float last_filt_velocity;//上一次的滤波后的速度
float velocity_sum=0;    //速度的累加

/*灰度PID参数修改处*/

float  Gray_kp = 0.5,
			 Gray_ki = 0.1,
			 Gray_kd = 0.1;

float filt_error;    		//滤波后误差 
float last_error;		//上次滤波后误差
float error_sum;    	//误差累加项




//速度环：位置式
int velocity_PID_value_L(int velocity)
{
	float a=0.5;                                           //滤波系数（反映滤波程度）
	float output = 0;

	filt_velocity = a*velocity + (1-a)*last_filt_velocity; //一阶速度滤波后实际速度
	filt_velocity = velocity_Goal - velocity;							 //本次误差
	velocity_sum +=  filt_velocity;                        //速度的累加
	Velocity_xianfu(2000);                                 //累加限幅
//	printf("\r\nvelocity_sum=%f",velocity_sum);
	output = VKp_L*filt_velocity + VKi_L*velocity_sum + VKd_L*(filt_velocity - last_filt_velocity);
	
	last_filt_velocity = filt_velocity;                    //此次速度记录为“上次速度”

	return output;
}

//速度环：位置式
int velocity_PID_value_R(int velocity)
{
	float a=0.5;                                           //滤波系数（反映滤波程度）
	float output = 0;

	filt_velocity = a*velocity + (1-a)*last_filt_velocity; //一阶速度滤波后实际速度
	filt_velocity = velocity_Goal - velocity;							 //本次误差
	velocity_sum +=  filt_velocity;                        //速度的累加
	Velocity_xianfu(2000);                                 //累加限幅
//	printf("\r\nvelocity_sum=%f",velocity_sum);
	output = VKp_R*filt_velocity + VKi_R*velocity_sum + VKd_R*(filt_velocity - last_filt_velocity);
	
	last_filt_velocity = filt_velocity;                    //此次速度记录为“上次速度”

	return output;
}


//灰度误差
float Gray_PID_value(float error)
{
	float a=0.5;                                           //滤波系数（反映滤波程度）
	float output = 0;
	if(error == 0)
		error_sum = 0;
	filt_error = a*error + (1-a)*last_error; 							 //一阶误差滤波
	error_sum += filt_error;															 //误差累积
	Error_xianfu(500);																			 //误差限幅
	
	output = Gray_kp * error + Gray_ki * error_sum + Gray_kd * (filt_error - last_error);
	
	last_error = filt_error;															 //上次误差记录
	return output;
	 
}


//error限幅：
void Error_xianfu(int max)
{
	if(error_sum>max)  error_sum=0;
	if(error_sum<-max) error_sum=-0;
}


//速度限幅：
void Velocity_xianfu(int max)
{
	if(velocity_sum>max)  velocity_sum=0;
	if(velocity_sum<-max) velocity_sum=-0;
}