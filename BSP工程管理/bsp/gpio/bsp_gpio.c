#include "bsp_gpio.h"

void GPIO_INIT(GPIO_Type *base, int pin, gpio_config *config)
{
    if(config->direction == Gpio_Input)/*输入*/
    {
        base->GDIR &= ~(1 << pin);
    }
    else if(config->direction == Gpio_Output)/*输出*/
    {
        base->GDIR |= (1 << pin);
        //默认输出输出
        GPIO_WRITE(base, pin, config->outputLogic);
    }

}

int GPIO_READ(GPIO_Type *base, int pin)
{
    return ((base->DR >> pin) & 0x1);
}

void GPIO_WRITE(GPIO_Type *base, int pin, int value)
{
    if (value == 0)
    {
        base->DR &= ~(1 << pin);
    }
    else if (value == 1)
    {
        base->DR |= (1 << pin);
    }
}

