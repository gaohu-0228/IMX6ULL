#ifndef _BSP_INT_H_
#define _BSP_INT_H_

#include "imx6ull.h"

/*中断处理函数类型*/
typedef void (*system_irq_handler) (unsigned int giccIar, void *param);

/*中断函数处理结构体*/
typedef struct sys_irq_handle
{
    system_irq_handler irqHandler; /*中断处理函数*/
    void *param; /*中断处理函数参数*/
} sys_irq_handle_t;

void int_init(void);
void system_irqtable_init(void);
void system_register_irqhandler(IRQn_Type irq, system_irq_handler handler, void *Param);
void system_irqhandler(unsigned int giccIar);
void default_irqhandler(unsigned int giccIar, void *param);



#endif