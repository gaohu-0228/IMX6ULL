#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"


int main()
{
    /*使能外设时钟*/
    clk_enable();
    /*IO初始化*/
    IO_init();

    while(1)
    {
        /*关灯*/
        LED_OFF();
        /*延时500ms*/
        delay(500);
        /*开灯*/
        LED_ON();
        /*延时500ms*/
        delay(500);
    }
}