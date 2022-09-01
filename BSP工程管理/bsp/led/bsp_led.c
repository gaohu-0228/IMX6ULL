#include "bsp_led.h"

void IO_init(void)
{
    /*IO复用GPIO1_IO03*/
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);

    /*设置GPIO1_IO03属性*/
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);

	/*设置GPIO1_IO03为输出*/
	GPIO1->GDIR = 0X0000008;

	/*设置GPIO_IO3输出低电平*/
	GPIO1->DR = 0x0;
}

/*打开LED灯*/
void LED_ON(void)
{
	GPIO1->DR &= ~(1<<3);
}

/*关闭LED灯*/
void LED_OFF(void)
{
	GPIO1->DR |= (1<<3);
}



