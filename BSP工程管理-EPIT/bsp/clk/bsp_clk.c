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
	int reg = 0;
	/*
	 * 设置内核主频为792MHz
	 * 1.先判断pll_sw_clk是选择pll_main_clk还是step_clk
	 * 2.pll_sw_clk选择的是pll_main_clk，则先切换到step_clk
	 * 3.调整pll_main_clk，然后pll_sw_clk切换到pll_main_clk
	 */
	if ((CCM->CCSR >> 2) & 0X1 == 0)
	{
		CCM->CCSR &= ~(1<<8);
		CCM->CCSR |= (1<<2);
	}

	CCM_ANALOG->PLL_ARM &= (1<<13) | (66 & 0X7F);
	CCM->CACRR &= ~(0X3);
	CCM->CCSR &= ~(1<<2);

	/*设置PLL2的4路PFD时钟和PLL3的4路PFD时钟*/
	CCM_ANALOG->PFD_528 &= ~(0x3F3F3F3F);
	reg |= 0x1B;
	reg |= 0x10 << 8;
	reg |= 0x18 << 16;
	reg |= 0x20 << 24;
	CCM_ANALOG->PFD_528 |= reg;

	CCM_ANALOG->PFD_480 &= ~(0x3F3F3F3F);
	reg |= 0xC;
	reg |= 0x10 << 8;
	reg |= 0x11 << 16;
	reg |= 0x13 << 24; 

	/*设置AHB、IPG和PERCLK根时钟设置*/
	CCM->CBCMR &= ~(3 << 18);
	CCM->CBCMR |= 1 << 18;
	CCM->CBCDR |= 1 << 25;
	while(CCM->CDHIPR & (1 << 5));

	CCM->CBCDR &= ~(3 << 8);
	CCM->CBCDR |= 1 << 8;

	CCM->CSCMR1 &= ~(1 << 6);
	CCM->CSCMR1 |= 0;
}