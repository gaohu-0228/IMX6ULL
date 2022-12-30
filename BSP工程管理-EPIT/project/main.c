#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_epit.h"


int main()
{
    /*中断初始化*/
    int_init();
    /*系统时钟初始化*/
    imx6ull_clkinit();
    /*使能外设时钟*/
    clk_enable();
    /*IO初始化*/
    IO_init();
    /*蜂鸣器初始化*/
    BEEP_INIT();
    /*按键初始化*/
    KEY_INTINIT();
    /*定时器初始化*/
    Epit_Init(0, 66000000/2);

    while(1)
    {
        delay(500);
    }
}