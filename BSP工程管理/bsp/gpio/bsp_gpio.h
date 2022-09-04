#ifndef _BSP_GPIO_H_
#define _BSP_GPIO_H_

#include "imx6ull.h"

typedef enum{
    Gpio_Input = 0,
    Gpio_Output = 1,
} gpio_direction;

typedef struct{
    gpio_direction direction;
    uint8_t outputLogic;
} gpio_config;

void GPIO_INIT(GPIO_Type *base, int pin, gpio_config *config);
void GPIO_READ(GPIO_Type *base, int pin);
void GPIO_WRITE(GPIO_Type *base, int pin, int value);



#endif