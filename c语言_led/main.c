#include "main.h"
#include <stdio.h>

/*使能所有外设时钟*/
void clk_enable(void)
{

}


/*LED对应的GPIO初始化*/
void IO_init(void)
{
    /*IO复用GPIO1_IO03*/

    /*设置GPIO1_IO03属性*/
}

/*打开LED灯*/
void LED_ON(void)
{

}

/*关闭LED灯*/
void LED_OFF(void)
{
	
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

}





