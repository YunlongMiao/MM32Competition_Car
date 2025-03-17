#include "GraySensor.h"
	

/* 8MHz ��5us�����27 */
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
		/* ���ʱ���½��� */
		gpio_set_level(gpio_clk, 0);
		gw_gray_delay(GW_GRAY_DELAY_TICK); //���ⲿ����Դ(4k ~ 10k����) �ɲ��Ӵ���

		ret |= gpio_get_level(gpio_dat) << i;

		/* ���ʱ��������,�ô�������������*/
		gpio_set_level(gpio_clk, 1);

		/* �ӳ���Ҫ��5us���� */
		gw_gray_delay(GW_GRAY_DELAY_TICK);
	}
	
	return ret;
}