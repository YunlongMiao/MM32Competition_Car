
/* 
* 文件名称          zf_driver_encoder
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK 5.37
* 适用平台          MM32F527X_E9P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "zf_driver_timer.h"

#include "zf_driver_encoder.h"

static uint8 encoder_dir_pin[ENCODER_NUM] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ENCODER 接口获取编码器计数
// 参数说明     encoder_n       ENCODER 模块号 参照 zf_driver_encoder.h 内 encoder_index_enum 枚举体定义
// 返回参数     int16           编码器数值
// 使用示例     encoder_get_count(TIM3_ENCODER);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
int16 encoder_get_count (encoder_index_enum encoder_n)
{
    uint32 result = 0;
    int16 return_value = 0;
    switch(encoder_n)
    {
        case TIM1_ENCODER:  result = TIM_GetCounterValue((TIM_Type *) TIM1);   break;
        case TIM2_ENCODER:  result = TIM_GetCounterValue((TIM_Type *) TIM2);   break;
        case TIM3_ENCODER:  result = TIM_GetCounterValue((TIM_Type *) TIM3);   break;
        case TIM4_ENCODER:  result = TIM_GetCounterValue((TIM_Type *) TIM4);   break;
        case TIM5_ENCODER:  result = TIM_GetCounterValue((TIM_Type *) TIM5);   break;
        case TIM8_ENCODER:  result = TIM_GetCounterValue((TIM_Type *) TIM8);   break;
        default: break;
    }
    if(0xFF == encoder_dir_pin[encoder_n])
    {
        return_value = (int16)result / 4;
    }
    else
    {
        return_value = (int16)result;
        if(!gpio_get_level((gpio_pin_enum)encoder_dir_pin[encoder_n]))
        {
             return_value = -return_value;
        }
    }
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ENCODER 清空编码器计数
// 参数说明     encoder_n       ENCODER 模块号 参照 zf_driver_encoder.h 内 encoder_index_enum 枚举体定义
// 返回参数     void
// 使用示例     encoder_clear_count(TIM3_ENCODER);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void encoder_clear_count (encoder_index_enum encoder_n)
{
    switch(encoder_n)
    {
        case TIM1_ENCODER:  TIM_DoSwTrigger((TIM_Type *) TIM1, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM2_ENCODER:  TIM_DoSwTrigger((TIM_Type *) TIM2, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM3_ENCODER:  TIM_DoSwTrigger((TIM_Type *) TIM3, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM4_ENCODER:  TIM_DoSwTrigger((TIM_Type *) TIM4, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM5_ENCODER:  TIM_DoSwTrigger((TIM_Type *) TIM5, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM8_ENCODER:  TIM_DoSwTrigger((TIM_Type *) TIM8, TIM_SWTRG_UPDATE_PERIOD);  break;
        default:    break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ENCODER 接口初始化 正交编码器使用
// 参数说明     encoder_n       ENCODER 模块号 参照 zf_driver_encoder.h 内 encoder_index_enum 枚举体定义
// 参数说明     ch1_pin         ENCODER 通道 1 参照 zf_driver_encoder.h 内 encoder_channel1_enum 枚举体定义
// 参数说明     ch2_pin         ENCODER 通道 2 参照 zf_driver_encoder.h 内 encoder_channel2_enum 枚举体定义
// 返回参数     void
// 使用示例     encoder_quad_init(TIM3_ENCODER, TIM3_ENCODER_CH1_B4, TIM3_ENCODER_CH2_B5);
// 备注信息     使用的编码器是正交编码器才可以使用此函数接口
//              如果是所谓的 “兼容正交编码器” 的编码器 麻烦先确定它到底是不是输出的正交编码器
//              这个接口只能给输出正交编码信号的编码器用
//-------------------------------------------------------------------------------------------------------------------
void encoder_quad_init (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    uint32 register_temp = 0;
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PWM 然后又初始化成 TIM1_ENCODER 这种用法是不允许的
    zf_assert(timer_funciton_check((timer_index_enum)encoder_n, TIMER_FUNCTION_ENCODER));
    zf_assert((ch1_pin & (encoder_n)) == (encoder_n));                          // ch1_pin 与 ch2_pin 必须与 encoder_n 匹配
    zf_assert((ch2_pin & (encoder_n)) == (encoder_n));                          // ch1_pin 与 ch2_pin 必须与 encoder_n 匹配

    timer_clock_enable((timer_index_enum)encoder_n);
    afio_init((gpio_pin_enum)((ch1_pin & 0xFFF000) >> 12), GPI, (gpio_af_enum)((ch1_pin & 0xF00) >> 8), GPI_FLOATING_IN);
    afio_init((gpio_pin_enum)((ch2_pin & 0xFFF000) >> 12), GPI, (gpio_af_enum)((ch2_pin & 0xF00) >> 8), GPI_FLOATING_IN);

    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = bus_clock;
    tim_init.StepFreqHz = bus_clock;
    tim_init.Period = 0x0000FFFF;
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;

    TIM_SlaveModeConf_Type tim_slave;
    tim_slave.In = TIM_SlaveIn_Alt0;
    tim_slave.Resp = TIM_SlaveResp_Alt3;

    TIM_InputCaptureConf_Type tim_input_conf;
    tim_input_conf.InDiv = TIM_InputCaptureInDiv_OnEach1Capture;
    tim_input_conf.InFilter = TIM_InputCaptureInFilter_Alt0;
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising;

    switch(encoder_n)
    {
        case TIM1_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM1, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM1, TIM_CHN_1, &tim_input_conf);
            TIM_EnableInputCapture((TIM_Type *) TIM1, TIM_CHN_2, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM1, &tim_slave);
            TIM_Start((TIM_Type *) TIM1);
        }break;
        case TIM2_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM2, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM2, TIM_CHN_1, &tim_input_conf);
            TIM_EnableInputCapture((TIM_Type *) TIM2, TIM_CHN_2, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM2, &tim_slave);
            TIM_Start((TIM_Type *) TIM2);
        }break;
        case TIM3_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM3, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM3, TIM_CHN_1, &tim_input_conf);
            TIM_EnableInputCapture((TIM_Type *) TIM3, TIM_CHN_2, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM3, &tim_slave);
            TIM_Start((TIM_Type *) TIM3);
        }break;
        case TIM4_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM4, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM4, TIM_CHN_1, &tim_input_conf);
            TIM_EnableInputCapture((TIM_Type *) TIM4, TIM_CHN_2, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM4, &tim_slave);
            TIM_Start((TIM_Type *) TIM4);
        }break;
        case TIM5_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM5, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM5, TIM_CHN_1, &tim_input_conf);
            TIM_EnableInputCapture((TIM_Type *) TIM5, TIM_CHN_2, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM5, &tim_slave);
            TIM_Start((TIM_Type *) TIM5);
        }break;
        case TIM8_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM8, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM8, TIM_CHN_1, &tim_input_conf);
            TIM_EnableInputCapture((TIM_Type *) TIM8, TIM_CHN_2, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM8, &tim_slave);
            TIM_Start((TIM_Type *) TIM8);
        }break;
        default:
        {
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ENCODER 接口初始化 带方向编码器使用
// 参数说明     encoder_n       ENCODER 模块号 参照 zf_driver_encoder.h 内 encoder_index_enum 枚举体定义
// 参数说明     ch1_pin         ENCODER 通道 1 参照 zf_driver_encoder.h 内 encoder_channel1_enum 枚举体定义
// 参数说明     ch2_pin         ENCODER 通道 2 参照 zf_driver_encoder.h 内 encoder_channel2_enum 枚举体定义
// 返回参数     void
// 使用示例     encoder_dir_init(TIM3_ENCODER, TIM3_ENCODER_CH1_B4, TIM3_ENCODER_CH2_B5);
// 备注信息     使用的编码器是带方向输出的增量式编码器才可以使用此函数接口
//              ch1_pin 将作为脉冲输入计数 ch2_pin 将作为计数方向控制引脚
//              此方式下 在出现反复正反转的情况下 计数方向将不是完全可靠的
//              只有读取时刻的 ch2_pin 的电平决定整个计数值的正负符号
//              同时 ch1_pin 只能选择 CH1 通道的引脚
//-------------------------------------------------------------------------------------------------------------------
void encoder_dir_init (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    uint32 register_temp = 0;
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PWM 然后又初始化成 TIM1_ENCODER 这种用法是不允许的
    zf_assert(timer_funciton_check((timer_index_enum)encoder_n, TIMER_FUNCTION_ENCODER));
    zf_assert((ch1_pin & (encoder_n)) == (encoder_n));                          // ch1_pin 与 ch2_pin 必须与 encoder_n 匹配
    zf_assert((ch2_pin & (encoder_n)) == (encoder_n));                          // ch1_pin 与 ch2_pin 必须与 encoder_n 匹配

    timer_clock_enable((timer_index_enum)encoder_n);
    afio_init((gpio_pin_enum)((ch1_pin & 0xFFF000) >> 12), GPI, (gpio_af_enum)((ch1_pin & 0xF00) >> 8), GPI_FLOATING_IN);
    gpio_init((gpio_pin_enum)((ch2_pin & 0xFFF000) >> 12), GPI, GPIO_LOW, GPI_FLOATING_IN);
    encoder_dir_pin[encoder_n] = ((ch2_pin & 0xFFF000) >> 12);

    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = bus_clock;
    tim_init.StepFreqHz = bus_clock;
    tim_init.Period = 0x0000FFFF;
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;

    TIM_SlaveModeConf_Type tim_slave;
    tim_slave.In = TIM_SlaveIn_Alt5;
    tim_slave.Resp = TIM_SlaveResp_Alt7;

    TIM_InputCaptureConf_Type tim_input_conf;
    tim_input_conf.InDiv = TIM_InputCaptureInDiv_OnEach1Capture;
    tim_input_conf.InFilter = TIM_InputCaptureInFilter_Alt0;
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising;

    switch(encoder_n)
    {
        case TIM1_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM1, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM1, TIM_CHN_1, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM1, &tim_slave);
            TIM_Start((TIM_Type *) TIM1);
        }break;
        case TIM2_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM2, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM2, TIM_CHN_1, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM2, &tim_slave);
            TIM_Start((TIM_Type *) TIM2);
        }break;
        case TIM3_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM3, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM3, TIM_CHN_1, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM3, &tim_slave);
            TIM_Start((TIM_Type *) TIM3);
        }break;
        case TIM4_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM4, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM4, TIM_CHN_1, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM4, &tim_slave);
            TIM_Start((TIM_Type *) TIM4);
        }break;
        case TIM5_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM5, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM5, TIM_CHN_1, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM5, &tim_slave);
            TIM_Start((TIM_Type *) TIM5);
        }break;
        case TIM8_ENCODER:
        {
            TIM_Init((TIM_Type *) TIM8, &tim_init);
            TIM_EnableInputCapture((TIM_Type *) TIM8, TIM_CHN_1, &tim_input_conf);
            TIM_EnableSlaveMode((TIM_Type *) TIM8, &tim_slave);
            TIM_Start((TIM_Type *) TIM8);
        }break;
        default:
        {
        }break;
    }
}
