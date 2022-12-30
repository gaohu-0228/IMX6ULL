#include "bsp_int.h"

/*中断嵌套计数器*/
static unsigned int irqNesting;

/*中断服务函数表*/
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];

 /*
 * @description : 中断初始化函数
 * @param : 无
 * @return : 无
 */
void int_init(void)
{
    GIC_Init();
    system_irqtable_init();
}

/*
 * @description : 初始化中断服务函数表
 * @param : 无
 * @return : 无
 */
void system_irqtable_init(void)
{
    unsigned int i = 0;
    irqNesting = 0;

    /*将所有的中断服务函数设置为默认值*/
    for (i = 0 ; i < NUMBER_OF_INT_VECTORS; i++)
    {
        system_register_irqhandler(i, default_irqhandler, NULL);
    }

}

/*
 * @description : 初始化中断服务函数表
 * @param - irq : 要注册的中断号
 * @param - handler : 要注册的中断处理函数
 * @param - Param : 中断服务处理函数参数 
 * @return : 无
 */
void system_register_irqhandler(IRQn_Type irq, system_irq_handler handler, void *Param)
{
    irqTable[irq].irqHandler = handler;
    irqTable[irq].param = Param;
}

/*
 * @description : c语言中断服务函数
 * @param - giccIar : 要注册的中断号 
 * @return : 无
 */
void system_irqhandler(unsigned int giccIar)
{
    unsigned int Num = giccIar & 0x3FF;

    /* 检查中断号是否符合要求 */
    if ((Num == 1020) || (Num > NUMBER_OF_INT_VECTORS))
    {
        return;
    }

    irqNesting++;

    irqTable[Num].irqHandler(Num, irqTable[Num].param);

    irqNesting--;
}

/*
 * @description : 默认中断服务函数
 * @param - giccIar : 要注册的中断号 
 * @param - param : 中断服务处理函数参数
 * @return : 无
 */
void default_irqhandler(unsigned int giccIar, void *param)
{
    while(1)
    {
    }
}
