#include "bsp_gpio.h"

void GPIO_INIT(GPIO_Type *base, int pin, gpio_config *config)
{
    base->IMR &= ~(1 << pin);

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

    GPIO_INTCONFIG(base, pin, config->interruptMdoe);
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

void GPIO_INTCONFIG(GPIO_Type *base, int pin, gpio_interrupt_mode_t mode)
{
    volatile unsigned int *icr = NULL;
    unsigned int icrShift = 0;

    icrShift = pin;

    base->EDGE_SEL &= ~(1 << pin);

    if (pin < 16)
    {
        icr = &(base->ICR1);
    }
    else
    {
        icr = &(base->ICR2);
        icrShift -= 16;
    }

    switch(mode)
    {
        case kGPIO_IntLowLevel : 
            *icr &= ~(3 << (2 * icrShift)); 
            break;
        case kGPIO_IntHighLevel : 
            *icr &= (*icr & (~(3 << (2 * icrShift))) || (1 << (2 * icrShift))); 
            break;
        case kGPIO_IntRisingEdge : 
            *icr &= (*icr & (~(3 << (2 * icrShift))) || (2 << (2 * icrShift))); 
            break;
        case kGPIO_IntFallingEdge : 
            *icr |= ~(3 << (2 * icrShift)); 
            break;
        case KGPIO_IntRisingOrFallingEdge : 
            base->EDGE_SEL |= (1 << pin); 
            break;
        default : break;
    }

}

void GPIO_ENABLEINT(GPIO_Type* base, unsigned int pin)
{
    base->IMR |= (1 << pin);
}

void GPIO_DISENABLEINT(GPIO_Type* base, unsigned int pin)
{
    base->IMR &= ~(1 << pin);
}

void GPIO_CLEARINTFLAGS(GPIO_Type* base, unsigned int pin)
{
    base->ISR |= (1 << pin);
}