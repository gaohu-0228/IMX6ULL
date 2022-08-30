#include "main.h"

/*使能所有外设时钟*/
void clk_enable(void)
{
	CCM_CCGR0 = 0XFFFFFFFF;
	CCM_CCGR1 = 0XFFFFFFFF;
	CCM_CCGR2 = 0XFFFFFFFF;
	CCM_CCGR3 = 0XFFFFFFFF;
	CCM_CCGR4 = 0XFFFFFFFF;
	CCM_CCGR5 = 0XFFFFFFFF;
	CCM_CCGR6 = 0XFFFFFFFF;
}


/*LED对应的GPIO初始化*/
void IO_init(void)
{
    /*IO复用GPIO1_IO03*/
	SW_MUX_GPIO1_IO03 = 0x05;

    /*设置GPIO1_IO03属性*/
	SW_PAD_GPIO1_IO03 = 0X10B0;

	/*设置GPIO1_IO03为输出*/
	GPIO1_GDIR = 0X0000008;

	/*设置GPIO_IO3输出低电平*/
	GPIO1_DR = 0x0;
}

/*打开LED灯*/
void LED_ON(void)
{
	GPIO1_DR &= ~(1<<3);
}

/*关闭LED灯*/
void LED_OFF(void)
{
	GPIO1_DR |= (1<<3);
}

void delay_short(volatile unsigned int n)
{
    while(n--)
	{
		
	}
}

/*延时函数，主频396MHz，延时大致1ms*/
void delay(volatile unsigned int n)
{
	while(n--)
	{
		delay_short(0x7ff);
	}
}

int main(void)
{
	/*开启所有外设时钟*/
	clk_enable();
	/*GPIO1_IO3初始化*/
	IO_init();

	while (1)
	{
		/*开灯*/
		LED_ON();
		/*延时500ms*/
		delay(500);
		/*关灯*/
		LED_OFF();
		/*延时500ms*/
		delay(500);
	}
	
}





