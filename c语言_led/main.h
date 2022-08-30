#ifndef _MAIN_H_
#define _MAIN_H_


/*
 * CCM相关寄存器地址
 */
#define CCM_CCGR0       *((volatile unsigned int*))
#define CCM_CCGR1       *((volatile unsigned int*))
#define CCM_CCGR2       *((volatile unsigned int*))
#define CCM_CCGR3       *((volatile unsigned int*))
#define CCM_CCGR4       *((volatile unsigned int*))
#define CCM_CCGR5       *((volatile unsigned int*))
#define CCM_CCGR6       *((volatile unsigned int*))

/*
 * IOMUX相关寄存器地址
 */
#define SW_MUX_GPIO1_IO03       *((volatile unsigned int*))
#define SW_PAD_GPIO1_IO03       *((volatile unsigned int*))

/*
 * GPIO1相关寄存器地址
 */
#define GPIO1_DR        *((volatile unsigned int*))
#define GPIO1_GDIR      *((volatile unsigned int*))
#define GPIO1_PSR       *((volatile unsigned int*))
#define GPIO1_ICR1      *((volatile unsigned int*))
#define GPIO1_ICR2      *((volatile unsigned int*))
#define GPIO1_IMR       *((volatile unsigned int*))
#define GPIO1_ISR       *((volatile unsigned int*))
#define GPIO1_EDGE_SEL  *((volatile unsigned int*))


#endif