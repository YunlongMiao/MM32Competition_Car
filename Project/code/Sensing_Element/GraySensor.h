#ifndef _GRAYSENSOR_H
#define _GRAYSENSOR_H

#include "zf_common_typedef.h"
#include "zf_common_headfile.h"

#define GW_GRAY_DELAY_TICK 5		//数据传输延时 us

#define gpio_clk B8
#define gpio_dat B9

void gw_gray_init();
uint8_t gw_gray_serial_read();

#endif