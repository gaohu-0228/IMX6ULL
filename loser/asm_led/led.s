.global _start

_start:
/*1、使能所有时钟*/
ldr r0, =0x020C4608     /*寄存器CCGR0*/
ldr r1, =0xFFFFFFFF
str r1, [r0]

ldr r0, =0x020C406C     /*寄存器CCGR1*/
str r1,[r0]

ldr r0, =0x020C4070     /*寄存器CCGR2*/
str r1,[r0]

ldr r0, =0x020C4074     /*寄存器CCGR3*/
str r1,[r0]

ldr r0, =0x020C4078     /*寄存器CCGR4*/
str r1,[r0]

ldr r0, =0x020C407C     /*寄存器CCGR5*/
str r1,[r0]

ldr r0, =0x020C4080     /*寄存器CCGR6*/
str r1,[r0]

/*2、设置GPIO1_IO03复用为GPIO1_IO03*/
ldr r0, =0x020E0068     /*将寄存器SW_MUX_GPIO1_IO03_BASE加载到r0中*/
ldr r1, =0x05           /*设置寄存器SW_MUX_GPIO1_IO03_BASE的MUX_MODE为5*/
str r1,[r0]

/* 3、配置 GPIO1_IO03 的 IO 属性
*bit 16:0 HYS 关闭
*bit [15:14]: 00 默认下拉
*bit [13]: 0 kepper 功能
*bit [12]: 1 pull/keeper 使能
*bit [11]: 0 关闭开路输出
*bit [7:6]: 10 速度 100Mhz
*bit [5:3]: 110 R0/6 驱动能力
*bit [0]: 0 低转换率
*/
ldr r0, =0X020E02F4 /*寄存器 SW_PAD_GPIO1_IO03_BASE */
ldr r1, =0X10B0
str r1,[r0]

/* 4、设置 GPIO1_IO03 为输出 */
ldr r0, =0X0209C004 /*寄存器 GPIO1_GDIR */
ldr r1, =0X0000008
str r1,[r0]

/* 5、打开 LED0
* 设置 GPIO1_IO03 输出低电平
*/
ldr r0, =0X0209C000 /*寄存器 GPIO1_DR */
ldr r1, =0
str r1,[r0]

/*
* 描述： loop 死循环
*/
loop:
    b loop