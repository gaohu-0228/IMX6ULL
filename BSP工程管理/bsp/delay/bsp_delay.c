#include "bsp_delay.h"

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