#include "pwm.h"

// Setup the timer. 
void Tim_Pwm_Init(void)
{
		TIM_Init_Type tim_init;
		TIM_OutputCompareConf_Type tim_outcomp_conf;	//TIM模块输出比较通道时设置输出比较特性。
	
	
//设置计数器	 
    tim_init.ClockFreqHz = CLOCK_SYS_FREQ;	//计数器时钟源频率
    tim_init.StepFreqHz = 1000000u; // 1MHz resolution. 
    tim_init.Period = 1000u - 1u;	// 1ms period, scale. 重装载值
    tim_init.EnablePreloadPeriod = false;	//不启用周期值预加载
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;	//计数器工作周期设置，重复计数和只记数一次
    tim_init.CountMode = TIM_CountMode_Increasing; //计数器计数方向，如果选择居中对齐模式将导致自由运行模式，这意味着添加到0xffff。
    TIM_Init(TIM_5, &tim_init);

// 设置PWM输出通道. 
    tim_outcomp_conf.ChannelValue = 0u;				//要与计数器比较的值
    tim_outcomp_conf.EnableFastOutput = false;	//启用对触发输入事件的快速响应
    tim_outcomp_conf.EnablePreLoadChannelValue = false; // 禁用预加载，立即放入数据. 
    tim_outcomp_conf.RefOutMode = TIM_OutputCompareRefOut_FallingEdgeOnMatch;	//PWM模式1 当计数器匹配通道值时的参考输出
    tim_outcomp_conf.ClearRefOutOnExtTrigger = false;	//外部触发高电平将清除参考
    tim_outcomp_conf.PinPolarity = TIM_PinPolarity_Rising; // 通道输出极性和互补输出将相反。 
    
		TIM_EnableOutputCompare(TIM_5, TIM_CHN_1, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_5, TIM_CHN_2, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_5, TIM_CHN_3, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_5, TIM_CHN_4, &tim_outcomp_conf);


// 启动输出比较. 
    TIM_EnableOutputCompareSwitch(TIM_5, true);

// 启动计数. 
    TIM_Start(TIM_5);
}



#if EN_TIM_PWM

// Setup the timer. 
void Tim_Pwm_Init(void)
{
    // Set the counter counting step. 
    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = CLOCK_SYS_FREQ;	//计数器时钟源频率
    tim_init.StepFreqHz = 1000000u; // 1MHz resolution. 
    tim_init.Period = 1000u - 1u;	// 1ms period, scale. 重装载值
    tim_init.EnablePreloadPeriod = false;	//不启用周期值预加载
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;	//计数器工作周期设置，重复计数和只记数一次
    tim_init.CountMode = TIM_CountMode_Increasing; //计数器计数方向，如果选择居中对齐模式将导致自由运行模式，这意味着添加到0xffff。
    TIM_Init(TIM_8, &tim_init);

    // 设置PWM输出通道. 
    TIM_OutputCompareConf_Type tim_outcomp_conf;	//TIM模块输出比较通道时设置输出比较特性。
    tim_outcomp_conf.ChannelValue = 0u;				//要与计数器比较的值
    tim_outcomp_conf.EnableFastOutput = false;	//启用对触发输入事件的快速响应
    tim_outcomp_conf.EnablePreLoadChannelValue = false; // 禁用预加载，立即放入数据. 
    tim_outcomp_conf.RefOutMode = TIM_OutputCompareRefOut_FallingEdgeOnMatch;	//当计数器匹配通道值时的参考输出
    tim_outcomp_conf.ClearRefOutOnExtTrigger = false;	//外部触发高电平将清除参考
    tim_outcomp_conf.PinPolarity = TIM_PinPolarity_Rising; // 通道输出极性和互补输出将相反。 
    
		TIM_EnableOutputCompare(TIM_8, TIM_CHN_1, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_8, TIM_CHN_2, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_8, TIM_CHN_3, &tim_outcomp_conf);
		TIM_EnableOutputCompare(TIM_8, TIM_CHN_4, &tim_outcomp_conf);

    // 使能比较输出？
//    TIM_EnableCompOutput(TIM_8, TIM_CHN_1, true);
//		TIM_EnableCompOutput(TIM_8, TIM_CHN_2, true);
//		TIM_EnableCompOutput(TIM_8, TIM_CHN_3, true);
//		TIM_EnableCompOutput(TIM_8, TIM_CHN_4, true);

    // 启动输出比较. 
    TIM_EnableOutputCompareSwitch(TIM_8, true);

    // 启动计数. 
    TIM_Start(TIM_8);
}
#endif
