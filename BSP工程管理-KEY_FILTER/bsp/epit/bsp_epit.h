#ifndef _BSP_EPIT_H_
#define _BSP_EPIT_H_

#include "imx6ull.h"

void Epit_Init(unsigned int frac, unsigned int value);
void Epit_irqhandler(void);


#endif