
#include "ADC_DEMO.h"


static  ADC_Type    *adc_index[2]       = {ADC1, ADC2};                         // ģ����������
static  uint8_t       adc_resolution[2]   = {ADC_12BIT, ADC_12BIT};               // �������ݱ���

//-------------------------------------------------------------------------------------------------------------------
// �������     adc ת������
// ����˵��     ch              ѡ�� adc ͨ�� (��� zf_driver_adc.h ��ö�� adc_channel_enum ����)
// ���ز���     uint16_t          ת���� adc ֵ
// ʹ��ʾ��     adc_convert(ADC1_CH0_A0);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16_t adc_convert (adc_channel_enum ch)
{
    uint32_t flag = ((ch & 0xFF0) >> 4);                                        // ��Ҫ��Ϊʲô�½�����
    uint32_t data = 0;                                                          // ��ȡ���ݻ�����

    ADC_EnableSeqSlot(adc_index[(ch & 0x0F)], 0, flag);
    ADC_DoSwTrigger(adc_index[(ch & 0x0F)], true);                              // ����ת��
    while((ADC_STATUS_CONV_SLOT_DONE | ADC_STATUS_CONV_SAMPLE_DONE) !=
        (ADC_GetStatus(adc_index[(ch & 0x0F)]) & (ADC_STATUS_CONV_SLOT_DONE | ADC_STATUS_CONV_SAMPLE_DONE)));
    ADC_ClearStatus(adc_index[(ch & 0x0F)], (ADC_STATUS_CONV_SLOT_DONE | ADC_STATUS_CONV_SAMPLE_DONE));
    data = ADC_GetSlotConvResult(adc_index[(ch & 0x0F)], 0, &flag);             // �Զ��׼� ���Ƕ�ȡ���
    return (data >> adc_resolution[(ch & 0x0F)]);                               // ���ݾ��������Ӧλ������
}

//-------------------------------------------------------------------------------------------------------------------
// �������     adc ��ֵ�˲�ת��
// ����˵��     ch              ѡ�� adc ͨ�� (��� zf_driver_adc.h ��ö�� adc_channel_enum ����)
// ����˵��     count           ��ֵ�˲�����
// ���ز���     uint16_t          ת���� adc ֵ
// ʹ��ʾ��     adc_mean_filter_convert(ADC1_CH0_A0, 5);                        // �ɼ�5�� Ȼ�󷵻�ƽ��ֵ
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16_t adc_mean_filter_convert (adc_channel_enum ch, const uint8_t count)
{
    uint8_t i = 0;
    uint32_t sum = 0;

    for(i = 0; i < count; i ++)
    {
        sum += adc_convert(ch);
    }

    return sum / count;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     adc ��ʼ��
// ����˵��     ch              ѡ�� adc ͨ�� (��� power.h ��ö�� adc_channel_enum ����)
// ����˵��     resolution      ѡ��ѡ��ͨ���ֱ���(���ͬһ�� adc ģ���ʼ��ʱ�����˲�ͬ�ķֱ��� �����һ����ʼ���ķֱ�����Ч)
// ���ز���     void
// ʹ��ʾ��     adc_init(ADC1_CH0_A0, ADC_8BIT);                                // ��ʼ�� A0 Ϊ ADC1 �� channel0 ���빦�� �ֱ���Ϊ8λ
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void adc_init (adc_channel_enum ch, adc_resolution_enum resolution)
{

    ADC_Init_Type adc_init;
    adc_resolution[(ch & 0x0F)] = resolution;                                   // �ȱ��ݾ���
    adc_init.Resolution = (ADC_Resolution_Type)resolution;                      // �����趨
    adc_init.ConvMode = ADC_ConvMode_SingleSlot;                                // ����ת��
    adc_init.Align = ADC_Align_Right;                                           // �����Ҷ���
    ADC_Init(adc_index[(ch & 0x0F)], &adc_init);                                // �����������ó�ʼ�� ADC

    if(ADC2_CH17_TEMP == ch)
    {
        ADC_EnableTempSensor(adc_index[(ch & 0x0F)], true);                     // �¶ȴ�����ʹ��
    }
    if(ADC2_CH18_VS == ch)
    {
        ADC_EnableVoltSensor(adc_index[(ch & 0x0F)], true);                     // �ڲ��ο���ѹʹ��
    }
    
    ADC_Enable(adc_index[(ch & 0x0F)], true);                                   // ʹ�� ADC
    ADC_DoAutoCalib(adc_index[(ch & 0x0F)]);                                    // ���� ADC Ӳ����У׼
}

#if 0
#include "hal_rcc.h"
#include "zf_common_clock.h"
#include "zf_driver_gpio.h"

#include "zf_driver_adc.h"

static  ADC_Type    *adc_index[2]       = {ADC1, ADC2};                         // ģ����������
static  uint8_t       adc_resolution[2]   = {ADC_12BIT, ADC_12BIT};               // �������ݱ���

//-------------------------------------------------------------------------------------------------------------------
// �������     adc ת������
// ����˵��     ch              ѡ�� adc ͨ�� (��� zf_driver_adc.h ��ö�� adc_channel_enum ����)
// ���ز���     uint16_t          ת���� adc ֵ
// ʹ��ʾ��     adc_convert(ADC1_CH0_A0);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16_t adc_convert (adc_channel_enum ch)
{
    uint32_t flag = ((ch & 0xFF0) >> 4);                                        // ��Ҫ��Ϊʲô�½�����
    uint32_t data = 0;                                                          // ��ȡ���ݻ�����

    ADC_EnableSeqSlot(adc_index[(ch & 0x0F)], 0, flag);
    ADC_DoSwTrigger(adc_index[(ch & 0x0F)], true);                              // ����ת��
    while((ADC_STATUS_CONV_SLOT_DONE | ADC_STATUS_CONV_SAMPLE_DONE) !=
        (ADC_GetStatus(adc_index[(ch & 0x0F)]) & (ADC_STATUS_CONV_SLOT_DONE | ADC_STATUS_CONV_SAMPLE_DONE)));
    ADC_ClearStatus(adc_index[(ch & 0x0F)], (ADC_STATUS_CONV_SLOT_DONE | ADC_STATUS_CONV_SAMPLE_DONE));
    data = ADC_GetSlotConvResult(adc_index[(ch & 0x0F)], 0, &flag);             // �Զ��׼� ���Ƕ�ȡ���
    return (data >> adc_resolution[(ch & 0x0F)]);                               // ���ݾ��������Ӧλ������
}

//-------------------------------------------------------------------------------------------------------------------
// �������     adc ��ֵ�˲�ת��
// ����˵��     ch              ѡ�� adc ͨ�� (��� zf_driver_adc.h ��ö�� adc_channel_enum ����)
// ����˵��     count           ��ֵ�˲�����
// ���ز���     uint16_t          ת���� adc ֵ
// ʹ��ʾ��     adc_mean_filter_convert(ADC1_CH0_A0, 5);                        // �ɼ�5�� Ȼ�󷵻�ƽ��ֵ
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16_t adc_mean_filter_convert (adc_channel_enum ch, const uint8_t count)
{
    uint8_t i = 0;
    uint32_t sum = 0;

    for(i = 0; i < count; i ++)
    {
        sum += adc_convert(ch);
    }

    return sum / count;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     adc ��ʼ��
// ����˵��     ch              ѡ�� adc ͨ�� (��� zf_driver_adc.h ��ö�� adc_channel_enum ����)
// ����˵��     resolution      ѡ��ѡ��ͨ���ֱ���(���ͬһ�� adc ģ���ʼ��ʱ�����˲�ͬ�ķֱ��� �����һ����ʼ���ķֱ�����Ч)
// ���ز���     void
// ʹ��ʾ��     adc_init(ADC1_CH0_A0, ADC_8BIT);                                // ��ʼ�� A0 Ϊ ADC1 �� channel0 ���빦�� �ֱ���Ϊ8λ
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void adc_init (adc_channel_enum ch, adc_resolution_enum resolution)
{
    if(ADC2_CH17_TEMP != ch && ADC2_CH18_VS != ch)                              // ȷ��������ͨ��
    {
        gpio_init((gpio_pin_enum)((ch & 0xFFF000) >> 12), GPI, GPIO_LOW, GPI_ANAOG_IN);
    }

    if(0x00 == (ch & 0x0F))
    {
        RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_ADC1, true);                      // ʹ�� ADC1 ʱ��
    }
    else
    {
        RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_ADC2, true);                      // ʹ�� ADC2 ʱ��
    }

    ADC_Init_Type adc_init;
    adc_resolution[(ch & 0x0F)] = resolution;                                   // �ȱ��ݾ���
    adc_init.Resolution = (ADC_Resolution_Type)resolution;                      // �����趨
    adc_init.ConvMode = ADC_ConvMode_SingleSlot;                                // ����ת��
    adc_init.Align = ADC_Align_Right;                                           // �����Ҷ���
    ADC_Init(adc_index[(ch & 0x0F)], &adc_init);                                // �����������ó�ʼ�� ADC

    if(ADC2_CH17_TEMP == ch)
    {
        ADC_EnableTempSensor(adc_index[(ch & 0x0F)], true);                     // �¶ȴ�����ʹ��
    }
    if(ADC2_CH18_VS == ch)
    {
        ADC_EnableVoltSensor(adc_index[(ch & 0x0F)], true);                     // �ڲ��ο���ѹʹ��
    }

    ADC_Enable(adc_index[(ch & 0x0F)], true);                                   // ʹ�� ADC
    ADC_DoAutoCalib(adc_index[(ch & 0x0F)]);                                    // ���� ADC Ӳ����У׼
}
#endif
