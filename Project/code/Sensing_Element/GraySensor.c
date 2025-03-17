#include "GraySensor.h"
	

/* 8MHz 下5us大概是27 */
static void gw_gray_delay(uint32_t delay)
{
	delay_us(delay);
}

void gw_gray_init()
{
	gpio_init(B9, GPI, GPIO_LOW, GPI_PULL_UP);
	gpio_init(B8, GPO, GPIO_LOW, GPO_PUSH_PULL);
}

//uint8_t gw_gray_serial_read(uint16_t gpio_clk, uint16_t gpio_dat)
uint8_t gw_gray_serial_read()
{
	uint8_t ret = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		/* 输出时钟下降沿 */
		gpio_set_level(gpio_clk, 0);
		gw_gray_delay(GW_GRAY_DELAY_TICK); //有外部上拉源(4k ~ 10k电阻) 可不加此行

		ret |= gpio_get_level(gpio_dat) << i;

		/* 输出时钟上升沿,让传感器更新数据*/
		gpio_set_level(gpio_clk, 1);

		/* 延迟需要在5us左右 */
		gw_gray_delay(GW_GRAY_DELAY_TICK);
	}
	
	return ret;
}