#include "bsp_beep.h"



void BEEP_INIT(void)
{
    /*IO复用GPIO5_IO01*/
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);

    /*设置GPIO1_IO03属性*/
	IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0X10B0);

	/*设置GPIO5_IO01为输出*/
	GPIO5->GDIR |= (1<<1);

	/*设置GPIO5_IO01输出高电平*/
	GPIO5->DR |= (1<<1);

}

void BEEP_ON(void)
{
    GPIO5->DR &= (0<<1);
}

void BEEP_OFF(void)
{
    GPIO5->DR |= (1<<1);
}