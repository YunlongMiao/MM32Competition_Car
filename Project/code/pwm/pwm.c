#include "pwm.h"

// Setup the timer. 
void Tim_Pwm_Init(void)
{
		TIM_Init_Type tim_init;
		TIM_OutputCompareConf_Type tim_outcomp_conf;	//TIMģ������Ƚ�ͨ��ʱ��������Ƚ����ԡ�
	
	
//���ü�����	 
    tim_init.ClockFreqHz = CLOCK_SYS_FREQ;	//������ʱ��ԴƵ��
    tim_init.StepFreqHz = 1000000u; // 1MHz resolution. 
    tim_init.Period = 1000u - 1u;	// 1ms period, scale. ��װ��ֵ
    tim_init.EnablePreloadPeriod = false;	//����������ֵԤ����
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;	//�����������������ã��ظ�������ֻ����һ��
    tim_init.CountMode = TIM_CountMode_Increasing; //�����������������ѡ����ж���ģʽ��������������ģʽ������ζ����ӵ�0xffff��
    TIM_Init(TIM_5, &tim_init);

// ����PWM���ͨ��. 
    tim_outcomp_conf.ChannelValue = 0u;				//Ҫ��������Ƚϵ�ֵ
    tim_outcomp_conf.EnableFastOutput = false;	//���öԴ��������¼��Ŀ�����Ӧ
    tim_outcomp_conf.EnablePreLoadChannelValue = false; // ����Ԥ���أ�������������. 
    tim_outcomp_conf.RefOutMode = TIM_OutputCompareRefOut_FallingEdgeOnMatch;	//PWMģʽ1 ��������ƥ��ͨ��ֵʱ�Ĳο����
    tim_outcomp_conf.ClearRefOutOnExtTrigger = false;	//�ⲿ�����ߵ�ƽ������ο�
    tim_outcomp_conf.PinPolarity = TIM_PinPolarity_Rising; // ͨ��������Ժͻ���������෴�� 
    
		TIM_EnableOutputCompare(TIM_5, TIM_CHN_1, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_5, TIM_CHN_2, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_5, TIM_CHN_3, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_5, TIM_CHN_4, &tim_outcomp_conf);


// ��������Ƚ�. 
    TIM_EnableOutputCompareSwitch(TIM_5, true);

// ��������. 
    TIM_Start(TIM_5);
}



#if EN_TIM_PWM

// Setup the timer. 
void Tim_Pwm_Init(void)
{
    // Set the counter counting step. 
    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = CLOCK_SYS_FREQ;	//������ʱ��ԴƵ��
    tim_init.StepFreqHz = 1000000u; // 1MHz resolution. 
    tim_init.Period = 1000u - 1u;	// 1ms period, scale. ��װ��ֵ
    tim_init.EnablePreloadPeriod = false;	//����������ֵԤ����
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;	//�����������������ã��ظ�������ֻ����һ��
    tim_init.CountMode = TIM_CountMode_Increasing; //�����������������ѡ����ж���ģʽ��������������ģʽ������ζ����ӵ�0xffff��
    TIM_Init(TIM_8, &tim_init);

    // ����PWM���ͨ��. 
    TIM_OutputCompareConf_Type tim_outcomp_conf;	//TIMģ������Ƚ�ͨ��ʱ��������Ƚ����ԡ�
    tim_outcomp_conf.ChannelValue = 0u;				//Ҫ��������Ƚϵ�ֵ
    tim_outcomp_conf.EnableFastOutput = false;	//���öԴ��������¼��Ŀ�����Ӧ
    tim_outcomp_conf.EnablePreLoadChannelValue = false; // ����Ԥ���أ�������������. 
    tim_outcomp_conf.RefOutMode = TIM_OutputCompareRefOut_FallingEdgeOnMatch;	//��������ƥ��ͨ��ֵʱ�Ĳο����
    tim_outcomp_conf.ClearRefOutOnExtTrigger = false;	//�ⲿ�����ߵ�ƽ������ο�
    tim_outcomp_conf.PinPolarity = TIM_PinPolarity_Rising; // ͨ��������Ժͻ���������෴�� 
    
		TIM_EnableOutputCompare(TIM_8, TIM_CHN_1, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_8, TIM_CHN_2, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_8, TIM_CHN_3, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_8, TIM_CHN_4, &tim_outcomp_conf);

    // ʹ�ܱȽ������
//    TIM_EnableCompOutput(TIM_8, TIM_CHN_1, true);
//		TIM_EnableCompOutput(TIM_8, TIM_CHN_2, true);
//		TIM_EnableCompOutput(TIM_8, TIM_CHN_3, true);
//		TIM_EnableCompOutput(TIM_8, TIM_CHN_4, true);

    // ��������Ƚ�. 
    TIM_EnableOutputCompareSwitch(TIM_8, true);

    // ��������. 
    TIM_Start(TIM_8);
}
#endif
