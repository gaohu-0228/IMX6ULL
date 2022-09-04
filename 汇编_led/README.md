要将imx6ull的IO作为GPIO使用，我们需要一下几步
1.使能GPIO对应的时钟。
2.设置寄存器IOMUXC_SW_MUX_CTL_PAD_XX_XX，设置IO的复用功能，使其复用为GPIO功能。
3.设置寄存器IOMUXC_SW_PAD_CTL_PAD_XX_XX，设置IO的上下拉，速度等等。
4.第2步已经将IO复用为了GPIO功能，所以需要配置GPIO，设置输入/输出、是否使用中断、默认输出电平等。