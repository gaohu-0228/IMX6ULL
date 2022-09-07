#include "bsp_clk.h"

/*使能所有外设时钟*/
void clk_enable(void)
{
	CCM->CCGR0 = 0XFFFFFFFF;
	CCM->CCGR1 = 0XFFFFFFFF;
	CCM->CCGR2 = 0XFFFFFFFF;
	CCM->CCGR3 = 0XFFFFFFFF;
	CCM->CCGR4 = 0XFFFFFFFF;
	CCM->CCGR5 = 0XFFFFFFFF;
	CCM->CCGR6 = 0XFFFFFFFF;
}

void imx6ull_clkinit(void)
{
	/*
	 * 设置内核主频为792MHz
	 * 1.先判断pll_sw_clk是选择pll_main_clk还是step_clk
	 * 2.pll_sw_clk选择的是pll_main_clk，则先切换到step_clk
	 * 3.调整pll_main_clk，然后pll_sw_clk切换到pll_main_clk
	 */
	if ((CCM->CCSR >> 2) & 0X1 == 0)
	{
		CCM->CCSR &= ~(1<<8);

	}


	/*设置PLL2、PLL3、PLL7时钟为528MHz、480MHz、480MHz*/

	/*设置PLL2的4路PFD时钟和PLL3的4路PFD时钟*/

	/*设置AHB、IPG和PERCLK根时钟设置*/	
}