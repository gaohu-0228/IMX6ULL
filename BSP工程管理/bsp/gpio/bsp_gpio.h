#ifndef _BSP_GPIO_H_
#define _BSP_GPIO_H_

#include "imx6ull.h"

typedef enum{
    Gpio_Input = 0,
    Gpio_Output = 1,
} gpio_direction;

typedef enum gpio_interrupt_mode
{
    kGPIO_NoIntmode = 0,
    kGPIO_IntLowLevel = 1,
    kGPIO_IntHighLevel = 2,
    kGPIO_IntRisingEdge = 3,
    kGPIO_IntFallingEdge = 4,
    KGPIO_IntRisingOrFallingEdge = 5,
} gpio_interrupt_mode_t;

typedef struct{
    gpio_direction direction;
    uint8_t outputLogic;
    gpio_interrupt_mode_t interruptMdoe;
} gpio_config;

void GPIO_INIT(GPIO_Type *base, int pin, gpio_config *config);
int GPIO_READ(GPIO_Type *base, int pin);
void GPIO_WRITE(GPIO_Type *base, int pin, int value);
void GPIO_INTCONFIG(GPIO_Type *base, int pin, gpio_interrupt_mode_t mode);
void GPIO_ENABLEINT(GPIO_Type* base, unsigned int pin);
void GPIO_CLEARINTFLAGS(GPIO_Type* base, unsigned int pin);


#endif