#include "encoder.h" 

/***************************************************
*   @FileName    encoder.c
 *  @brief   定时器编码器模式配置文件，其中时钟初始化在clock_init.c中进行，IO配置在pin_init.c中进行，部分宏定义在board_init.h中  
 *  @date    2023/06/24
 *  @author  苗云龙
****************************************************/



/* Setup the timer. */
void Encoder_Tim_Init(void)
{
		/* 设置计数器计数步长*/
    TIM_Init_Type tim_init;		//结构体成员数为6个
    /* 启用输入捕获*/
    TIM_InputCaptureConf_Type tim_input_conf;
	   /* Enable slave mode. 启用从模式。*/
    TIM_SlaveModeConf_Type tim_slave_conf;
	
	
	
//设置计数器	
    tim_init.ClockFreqHz = CLOCK_SYS_FREQ;	//计数器时钟源频率
    tim_init.StepFreqHz = CLOCK_SYS_FREQ; /*步长值。计数器频率= ClockSourceFreqHz / (ClockSourceDiv+1)不影响StepFreqHz， StepFreqHz would not affect. */
    tim_init.Period = 2000u - 1u;	//计数器重装载值，从0到period
    tim_init.EnablePreloadPeriod = false;	//启用周期值预加载。如果启用，将在下一个周期更新，否则立即更新。
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;	//计数器工作周期设置，重复计数和只记数一次
    tim_init.CountMode = TIM_CountMode_Increasing; /*计数器计数方向，如果选择居中对齐模式将导致自由运行模式，这意味着添加到0xffff。 If choose center aligned mode will lead to free run mode, which means adding until 0xffff. */
    
		TIM_Init(TIM_3, &tim_init);
		TIM_Init(TIM_4, &tim_init);
	
	
	
//使能定时器中断
		//TIM3
    NVIC_EnableIRQ(TIM3_IRQn);		//使能中断
    TIM_EnableInterrupts(TIM_3, TIM_INT_UPDATE_PERIOD, true);	//允许定时器更新中断，定时器更新周期中断切换器
		//TIM4
		NVIC_EnableIRQ(TIM4_IRQn);		//使能中断
    TIM_EnableInterrupts(TIM_4, TIM_INT_UPDATE_PERIOD, true);	//允许定时器更新中断，定时器更新周期中断切换器


	
//启用输入捕获
		//TIM3设置
    tim_input_conf.InDiv = TIM_InputCaptureInDiv_OnEach1Capture;	//0，过滤输入的除法
    tim_input_conf.InFilter = TIM_InputCaptureInFilter_Alt0;			//0，初始输入的滤波器采样时间。
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising; /*不变，设置输出引脚的极性，切换到TIM_PinPolarity_Falling，如果需要反转通道1输入的计数器下流。 Switch to TIM_PinPolarity_Falling if need reversing the channel 1 input for underflow of the counter. */
    TIM_EnableInputCapture(TIM_3, TIM_CHN_1, &tim_input_conf);
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising;
    TIM_EnableInputCapture(TIM_3, TIM_CHN_2, &tim_input_conf);
		//TIM4设置
		tim_input_conf.PinPolarity = TIM_PinPolarity_Rising;
    TIM_EnableInputCapture(TIM_4, TIM_CHN_1, &tim_input_conf);
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising;
    TIM_EnableInputCapture(TIM_4, TIM_CHN_2, &tim_input_conf);



//从模式设置
		//TIM3设置
    tim_slave_conf.In = TIM_SlaveIn_Alt0;/* 输入从计时器的触发选择，在编码器模式下，输入不受影响Input would not afferct under encoder mode. */
    tim_slave_conf.Resp = TIM_SlaveResp_Alt3;/* 从定时器计数器响应其输入触发器，编码器模式3. */
		
    TIM_EnableSlaveMode(TIM_3, &tim_slave_conf);
		//TIM4设置
		TIM_EnableSlaveMode(TIM_4, &tim_slave_conf);

//启动计数
    TIM_Start(TIM_3);
		TIM_Start(TIM_4);
}




//TIM3中断服务函数
void TIM3_IRQHandler(void)
{
    uint32_t flags = TIM_GetInterruptStatus(TIM_3);
    if ( 0u != (flags & TIM_STATUS_UPDATE_PERIOD ) )	//检查更新状态  TIM_STATUS_UPDATE_PERIOD 定时器更新周期中断标志
    {
        printf("update\r\n");
    }
    TIM_ClearInterruptStatus(TIM_3, flags);
}




//TIM4中断服务函数
void TIM4_IRQHandler(void)
{
    uint32_t flags = TIM_GetInterruptStatus(TIM_4);
    if ( 0u != (flags & TIM_STATUS_UPDATE_PERIOD ) ) 
    {
        printf("update\r\n");
    }
    TIM_ClearInterruptStatus(TIM_4, flags);
}


