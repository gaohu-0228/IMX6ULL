#include "bsp_key.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"
#include "bsp_int.h"
#include "bsp_beep.c"

void KEY_INTINIT(void)
{
    gpio_config config;

    /*IO复用GPIO1_IO18*/
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    
    /*配置IO属性*/
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    /*初始化GPIO为中断模式*/
    config.direction = Gpio_Input;
    config.interruptMdoe = kGPIO_IntFallingEdge;
    config.outputLogic = 1;
    GPIO_INIT(GPIO1, 18, &config);

    /*使能GIC中断、注册中断服务函数、使能GPIO中断*/
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);

    system_register_irqhandler();
}

/*
 * @description : KEY中断处理函数
 * @param       : 无
 * @return      ：无
 */
void key_irqhandler(void)
{
    static char state = 0;

    delay(10);
    if (GPIO_READ(GPIO1, 18) == 0)
    {
        state = !state;
        BEEP_SWITCH(state);
    }

    GPIO_CLEARINTFLAGS(GPIO1, 18);
}