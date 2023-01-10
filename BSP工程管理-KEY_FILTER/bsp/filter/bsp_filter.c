#include "bsp_filter.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_beep.h"



/*
 * @description : 按键初始化函数
 * @param  : 无
 * @return : 无
 */
void filterkey_init(void)
{
    gpio_config key_config;

    /*初始化GPIO*/
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    /*初始化GPIO为中断*/
    key_config.direction = Gpio_Input;
    key_config.outputLogic = 1;
    key_config.interruptMdoe = kGPIO_IntFallingEdge;

    GPIO_INIT(GPIO1, 18, &key_config);

    /*使能GPIO中断且注册中断处理函数*/
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler)gpio1_16_31_irqhandler, NULL);

    /*使能GPIO1_IO18的中断*/
    GPIO_ENABLEINT(GPIO1, 18);

    /*定时器初始化*/
    filtertimer_init(66000000/100);

}

/*
 * @description : EPIT定时器初始化
 * @param - value: 倒计数值
 * @return : 无
 */
void filtertimer_init(unsigned int value)
{
    EPIT1->CR = 0;
    EPIT1->CR = (1<<24 | 1<<3 | 1<<2 | 1<<1);
    EPIT1->LR = value;
    EPIT1->CMPR = 0;

    /*使能EPIT1中断并注册中断处理函数*/
    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn, (system_irq_handler)filtertimer_irqhandler, NULL);
}

/*
 * @description : 关闭定时器
 * @param : 无
 * @return : 无
 */
void filtertimer_stop(void)
{
    EPIT1->CR &= ~(1 << 0);
}

/*
 * @description : 重启定时器
 * @param - value: 倒计数值
 * @return : 无
 */
void filtertimer_restart(unsigned int value)
{
    EPIT1->CR &= ~(1 << 0);
    EPIT1->LR = value;
    EPIT1->CR |= (1 << 0);
}

/*
 * @description : 定时器中断处理函数
 * @param : 倒计数值
 * @return : 无
 */
void filtertimer_irqhandler(void)
{
    static unsigned char state = 0;
    
    if(EPIT1->SR & (1 << 0))
    {
        filtertimer_stop();
        if(GPIO_READ(GPIO1, 18) == 0);
        {
            state = !state;
            BEEP_SWITCH(state);
        }
    }

    EPIT1->SR |= 1 << 0;
}

/*
 * @description : GPIO中断处理函数
 * @param : 倒计数值
 * @return : 无
 */
void gpio1_16_31_irqhandler(void)
{
    filtertimer_restart(66000000/100);
    GPIO_CLEARINTFLAGS(GPIO1, 18);
}