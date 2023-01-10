#ifndef _BSP_FIlTER_H_
#define _BSP_FIlTER_H_


#include "imx6ull.h"

void filterkey_init(void);
void filtertimer_init(unsigned int value);
void filtertimer_stop(void);
void filtertimer_restart(unsigned int value);
void filtertimer_irqhandler(void);
void gpio1_16_31_irqhandler(void);

#endif