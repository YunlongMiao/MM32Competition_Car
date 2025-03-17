#include "encoder.h" 

/***************************************************
*   @FileName    encoder.c
 *  @brief   ��ʱ��������ģʽ�����ļ�������ʱ�ӳ�ʼ����clock_init.c�н��У�IO������pin_init.c�н��У����ֺ궨����board_init.h��  
 *  @date    2023/06/24
 *  @author  ������
****************************************************/



/* Setup the timer. */
void Encoder_Tim_Init(void)
{
		/* ���ü�������������*/
    TIM_Init_Type tim_init;		//�ṹ���Ա��Ϊ6��
    /* �������벶��*/
    TIM_InputCaptureConf_Type tim_input_conf;
	   /* Enable slave mode. ���ô�ģʽ��*/
    TIM_SlaveModeConf_Type tim_slave_conf;
	
	
	
//���ü�����	
    tim_init.ClockFreqHz = CLOCK_SYS_FREQ;	//������ʱ��ԴƵ��
    tim_init.StepFreqHz = CLOCK_SYS_FREQ; /*����ֵ��������Ƶ��= ClockSourceFreqHz / (ClockSourceDiv+1)��Ӱ��StepFreqHz�� StepFreqHz would not affect. */
    tim_init.Period = 2000u - 1u;	//��������װ��ֵ����0��period
    tim_init.EnablePreloadPeriod = false;	//��������ֵԤ���ء�������ã�������һ�����ڸ��£������������¡�
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;	//�����������������ã��ظ�������ֻ����һ��
    tim_init.CountMode = TIM_CountMode_Increasing; /*�����������������ѡ����ж���ģʽ��������������ģʽ������ζ����ӵ�0xffff�� If choose center aligned mode will lead to free run mode, which means adding until 0xffff. */
    
		TIM_Init(TIM_3, &tim_init);
		TIM_Init(TIM_4, &tim_init);
	
	
	
//ʹ�ܶ�ʱ���ж�
		//TIM3
    NVIC_EnableIRQ(TIM3_IRQn);		//ʹ���ж�
    TIM_EnableInterrupts(TIM_3, TIM_INT_UPDATE_PERIOD, true);	//����ʱ�������жϣ���ʱ�����������ж��л���
		//TIM4
		NVIC_EnableIRQ(TIM4_IRQn);		//ʹ���ж�
    TIM_EnableInterrupts(TIM_4, TIM_INT_UPDATE_PERIOD, true);	//����ʱ�������жϣ���ʱ�����������ж��л���


	
//�������벶��
		//TIM3����
    tim_input_conf.InDiv = TIM_InputCaptureInDiv_OnEach1Capture;	//0����������ĳ���
    tim_input_conf.InFilter = TIM_InputCaptureInFilter_Alt0;			//0����ʼ������˲�������ʱ�䡣
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising; /*���䣬����������ŵļ��ԣ��л���TIM_PinPolarity_Falling�������Ҫ��תͨ��1����ļ����������� Switch to TIM_PinPolarity_Falling if need reversing the channel 1 input for underflow of the counter. */
    TIM_EnableInputCapture(TIM_3, TIM_CHN_1, &tim_input_conf);
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising;
    TIM_EnableInputCapture(TIM_3, TIM_CHN_2, &tim_input_conf);
		//TIM4����
		tim_input_conf.PinPolarity = TIM_PinPolarity_Rising;
    TIM_EnableInputCapture(TIM_4, TIM_CHN_1, &tim_input_conf);
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising;
    TIM_EnableInputCapture(TIM_4, TIM_CHN_2, &tim_input_conf);



//��ģʽ����
		//TIM3����
    tim_slave_conf.In = TIM_SlaveIn_Alt0;/* ����Ӽ�ʱ���Ĵ���ѡ���ڱ�����ģʽ�£����벻��Ӱ��Input would not afferct under encoder mode. */
    tim_slave_conf.Resp = TIM_SlaveResp_Alt3;/* �Ӷ�ʱ����������Ӧ�����봥������������ģʽ3. */
		
    TIM_EnableSlaveMode(TIM_3, &tim_slave_conf);
		//TIM4����
		TIM_EnableSlaveMode(TIM_4, &tim_slave_conf);

//��������
    TIM_Start(TIM_3);
		TIM_Start(TIM_4);
}




//TIM3�жϷ�����
void TIM3_IRQHandler(void)
{
    uint32_t flags = TIM_GetInterruptStatus(TIM_3);
    if ( 0u != (flags & TIM_STATUS_UPDATE_PERIOD ) )	//������״̬  TIM_STATUS_UPDATE_PERIOD ��ʱ�����������жϱ�־
    {
        printf("update\r\n");
    }
    TIM_ClearInterruptStatus(TIM_3, flags);
}




//TIM4�жϷ�����
void TIM4_IRQHandler(void)
{
    uint32_t flags = TIM_GetInterruptStatus(TIM_4);
    if ( 0u != (flags & TIM_STATUS_UPDATE_PERIOD ) ) 
    {
        printf("update\r\n");
    }
    TIM_ClearInterruptStatus(TIM_4, flags);
}


