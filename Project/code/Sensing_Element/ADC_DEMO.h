#ifndef _ADC_DEMO_H
#define _ADC_DEMO_H


#include "board_init.h" 


typedef enum                                                                    // 枚举 ADC 引脚通道  此枚举定义不允许用户修改
{
    ADC1_CH0_A0         = 0x000000,                                             // 0x 000[A0 ] 00[CH0 ] 0[ADC1]
    ADC1_CH1_A1         = 0x001010,                                             // 0x 001[A1 ] 01[CH1 ] 0[ADC1]
    ADC1_CH2_A2         = 0x002020,                                             // 0x 002[A2 ] 02[CH2 ] 0[ADC1]
    ADC1_CH3_A3         = 0x003030,                                             // 0x 003[A3 ] 03[CH3 ] 0[ADC1]
    ADC1_CH4_A4         = 0x004040,                                             // 0x 004[A4 ] 04[CH4 ] 0[ADC1]
    ADC1_CH5_A5         = 0x005050,                                             // 0x 005[A5 ] 05[CH5 ] 0[ADC1]
    ADC1_CH6_A6         = 0x006060,                                             // 0x 006[A6 ] 06[CH6 ] 0[ADC1]
    ADC1_CH7_A7         = 0x007070,                                             // 0x 007[A7 ] 07[CH7 ] 0[ADC1]
    ADC1_CH8_B0         = 0x020080,                                             // 0x 020[B0 ] 08[CH8 ] 0[ADC1]
    ADC1_CH9_B1         = 0x021090,                                             // 0x 021[B1 ] 09[CH9 ] 0[ADC1]
    ADC1_CH10_C0        = 0x0400A0,                                             // 0x 040[C0 ] 0A[CH10] 0[ADC1]
    ADC1_CH11_C1        = 0x0410B0,                                             // 0x 041[C1 ] 0B[CH11] 0[ADC1]
    ADC1_CH12_C2        = 0x0420C0,                                             // 0x 042[C2 ] 0C[CH12] 0[ADC1]
    ADC1_CH13_C3        = 0x0430D0,                                             // 0x 043[C3 ] 0D[CH13] 0[ADC1]
    ADC1_CH14_F10       = 0x0AA0E0,                                             // 0x 0AA[F10] 0E[CH14] 0[ADC1]
    ADC1_CH15_F9        = 0x0A90F0,                                             // 0x 0A9[F9 ] 0F[CH15] 0[ADC1]
    ADC1_CH16_F8        = 0x0A8100,                                             // 0x 0A8[F8 ] 10[CH16] 0[ADC1]
    ADC1_CH17_F7        = 0x0A7110,                                             // 0x 0A7[F7 ] 11[CH17] 0[ADC1]
    ADC1_CH18_F6        = 0x0A6120,                                             // 0x 0A6[F6 ] 12[CH18] 0[ADC1]

    ADC2_CH0_A0         = 0x000001,                                             // 0x 000[A0 ] 00[CH0 ] 1[ADC2]
    ADC2_CH1_A1         = 0x001011,                                             // 0x 001[A1 ] 01[CH1 ] 1[ADC2]
    ADC2_CH2_A2         = 0x002021,                                             // 0x 002[A2 ] 02[CH2 ] 1[ADC2]
    ADC2_CH3_A3         = 0x003031,                                             // 0x 003[A3 ] 03[CH3 ] 1[ADC2]
    ADC2_CH4_A4         = 0x004041,                                             // 0x 004[A4 ] 04[CH4 ] 1[ADC2]
    ADC2_CH5_A5         = 0x005051,                                             // 0x 005[A5 ] 05[CH5 ] 1[ADC2]
    ADC2_CH6_A6         = 0x006061,                                             // 0x 006[A6 ] 06[CH6 ] 1[ADC2]
    ADC2_CH7_A7         = 0x007071,                                             // 0x 007[A7 ] 07[CH7 ] 1[ADC2]
    ADC2_CH8_B0         = 0x020081,                                             // 0x 020[B0 ] 08[CH8 ] 1[ADC2]
    ADC2_CH9_B1         = 0x021091,                                             // 0x 021[B1 ] 09[CH9 ] 1[ADC2]
    ADC2_CH10_C0        = 0x0400A1,                                             // 0x 040[C0 ] 0A[CH10] 1[ADC2]
    ADC2_CH11_C1        = 0x0410B1,                                             // 0x 041[C1 ] 0B[CH11] 1[ADC2]
    ADC2_CH12_E7        = 0x0870C1,                                             // 0x 087[E7 ] 0C[CH12] 1[ADC2]
    ADC2_CH13_E8        = 0x0880D1,                                             // 0x 088[E8 ] 0D[CH13] 1[ADC2]
    ADC2_CH14_C4        = 0x0440E1,                                             // 0x 044[C4 ] 0E[CH14] 1[ADC2]
    ADC2_CH15_C5        = 0x0450F1,                                             // 0x 045[C5 ] 0F[CH15] 1[ADC2]
    ADC2_CH16_E9        = 0x089101,                                             // 0x 089[E9 ] 10[CH16] 1[ADC2]
    ADC2_CH17_TEMP      = 0xFFF111,                                             // 0x FFF[NC ] 11[CH17] 1[ADC2] 温度传感器通道
    ADC2_CH18_VS        = 0xFFF121,                                             // 0x FFF[NC ] 12[CH18] 1[ADC2] 内部参考电压通道
}adc_channel_enum;

typedef enum                                                                    // 枚举 ADC 分辨率   此枚举定义不允许用户修改
{
    ADC_12BIT           = ADC_Resolution_Alt0,                                  // 12 位分辨率
    ADC_11BIT           = ADC_Resolution_Alt1,                                  // 11 位分辨率
    ADC_10BIT           = ADC_Resolution_Alt2,                                  // 10 位分辨率
    ADC_9BIT            = ADC_Resolution_Alt3,                                  // 9  位分辨率
    ADC_8BIT            = ADC_Resolution_Alt4,                                  // 8  位分辨率
}adc_resolution_enum;

uint16_t      adc_convert             (adc_channel_enum ch);
uint16_t      adc_mean_filter_convert (adc_channel_enum ch, const uint8_t count);
void        adc_init                (adc_channel_enum ch, adc_resolution_enum resolution);





#endif