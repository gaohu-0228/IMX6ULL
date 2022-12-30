#include "bsp_epit.h"


/*
 * @description : 初始化 EPIT 定时器.
 * EPIT 定时器是 32 位向下计数器,时钟源使用 ipg=66Mhz
 * @param – frac: 分频值，范围为 0~4095，分别对应 1~4096 分频。
 * @param - value : 倒计数值。
 * @return : 无
 */
void EpitInit(unsigned int frac, unsigned int value)
{
    if(frac > 0xfff)
        frac = 0xfff;
    EPIT1->CR = 0;

    /*
     *EPIT时钟源选择位（bit25:24）：选择Peripheral时钟（ipg_clk=66MHz）
     *EPIT时钟源分频值（bit15:4）：可设置范围0~4095，分别对应1~4096分频
     *EPIT工作模式（bit3）：为0时为free-running模式，为1时为set-and-forget模式
     *比较中断使能位（bit2）：为0时为关闭比较中断，为1时为使能比较中断
     *设置计数器初始值（bit1）：为0时计数器初始值等于上次关闭EPIT定时器以后计数器里面的值，为1的时候来源于加载寄存器
     *EPIT使能位（bit0）：为0时关闭EPIT，为1时使能EPIT
     */

    EPIT1->CR = (1<<24 | frac<<4 | 1<<3 | 1<<2 | 1<<1);
    EPIT1->LR = value;
    EPIT1->CMPR = 0;

    /*使能GIC钟对应的中断*/
    GIC_EnableIRQ(EPIT1_IRQn);
}