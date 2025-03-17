#include "pid.h"

//�ٶȻ�PI����:
float VKp_L =  0.2,	
			VKi_L =  0.1,
			VKd_L =  0.3; 

//�ٶȻ�PI����:
float VKp_R =  0.3,	
			VKi_R =  0.125,
			VKd_R =  0.3; 

//extern float VKp,VKi;    //�ٶȻ�����
float velocity_Goal = 300.0;
float filt_velocity;     //�˲�����ٶ�
float last_filt_velocity;//��һ�ε��˲�����ٶ�
float velocity_sum=0;    //�ٶȵ��ۼ�

/*�Ҷ�PID�����޸Ĵ�*/

float  Gray_kp = 0.5,
			 Gray_ki = 0.1,
			 Gray_kd = 0.1;

float filt_error;    		//�˲������ 
float last_error;		//�ϴ��˲������
float error_sum;    	//����ۼ���




//�ٶȻ���λ��ʽ
int velocity_PID_value_L(int velocity)
{
	float a=0.5;                                           //�˲�ϵ������ӳ�˲��̶ȣ�
	float output = 0;

	filt_velocity = a*velocity + (1-a)*last_filt_velocity; //һ���ٶ��˲���ʵ���ٶ�
	filt_velocity = velocity_Goal - velocity;							 //�������
	velocity_sum +=  filt_velocity;                        //�ٶȵ��ۼ�
	Velocity_xianfu(2000);                                 //�ۼ��޷�
//	printf("\r\nvelocity_sum=%f",velocity_sum);
	output = VKp_L*filt_velocity + VKi_L*velocity_sum + VKd_L*(filt_velocity - last_filt_velocity);
	
	last_filt_velocity = filt_velocity;                    //�˴��ٶȼ�¼Ϊ���ϴ��ٶȡ�

	return output;
}

//�ٶȻ���λ��ʽ
int velocity_PID_value_R(int velocity)
{
	float a=0.5;                                           //�˲�ϵ������ӳ�˲��̶ȣ�
	float output = 0;

	filt_velocity = a*velocity + (1-a)*last_filt_velocity; //һ���ٶ��˲���ʵ���ٶ�
	filt_velocity = velocity_Goal - velocity;							 //�������
	velocity_sum +=  filt_velocity;                        //�ٶȵ��ۼ�
	Velocity_xianfu(2000);                                 //�ۼ��޷�
//	printf("\r\nvelocity_sum=%f",velocity_sum);
	output = VKp_R*filt_velocity + VKi_R*velocity_sum + VKd_R*(filt_velocity - last_filt_velocity);
	
	last_filt_velocity = filt_velocity;                    //�˴��ٶȼ�¼Ϊ���ϴ��ٶȡ�

	return output;
}


//�Ҷ����
float Gray_PID_value(float error)
{
	float a=0.5;                                           //�˲�ϵ������ӳ�˲��̶ȣ�
	float output = 0;
	if(error == 0)
		error_sum = 0;
	filt_error = a*error + (1-a)*last_error; 							 //һ������˲�
	error_sum += filt_error;															 //����ۻ�
	Error_xianfu(500);																			 //����޷�
	
	output = Gray_kp * error + Gray_ki * error_sum + Gray_kd * (filt_error - last_error);
	
	last_error = filt_error;															 //�ϴ�����¼
	return output;
	 
}


//error�޷���
void Error_xianfu(int max)
{
	if(error_sum>max)  error_sum=0;
	if(error_sum<-max) error_sum=-0;
}


//�ٶ��޷���
void Velocity_xianfu(int max)
{
	if(velocity_sum>max)  velocity_sum=0;
	if(velocity_sum<-max) velocity_sum=-0;
}