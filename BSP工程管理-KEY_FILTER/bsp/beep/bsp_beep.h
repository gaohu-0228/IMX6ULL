#ifndef _BSP_BEEP_H_
#define _BSP_BEEP_H_

#include "imx6ull.h"

void BEEP_INIT(void);
void BEEP_ON(void);
void BEEP_OFF(void);
void BEEP_SWITCH(uint32_t state);

#endif