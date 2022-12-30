#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"


int main()
{
    /*使能外设时钟*/
    clk_enable();
    /*IO初始化*/
    IO_init();
    /*蜂鸣器初始化*/
    BEEP_INIT();

    while(1)
    {

    }
}