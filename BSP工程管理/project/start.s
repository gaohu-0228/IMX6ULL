.global _start

.global _bss_start
_bss_start:
    .word bss_start

.global _bss_end
_bss_end:
    .word bss_end

_start:
    ldr pc, =Reset_Handler      /*复位中断*/
    ldr pc, =Undefined_Handler  /*未定义指令中断*/
    ldr pc, =SVC_Handler        /*SVC中断*/
    ldr pc, =PrefAbort_Handler  /*指令预取中止中断*/
    ldr pc, =DataAbort_Handler  /*数据访问中止中断*/
    ldr pc, =IRQ_Handler        /*IRQ中断*/
    ldr pc, =FIQ_Handler        /*FIQ中断*/

/*复位中断*/
Reset_Handler:

    cpsid i                     /*关闭IRQ中断*/
    /*关闭ICache、DCache和MMU*/
    mrc p15, 0, r0, c1, c0, 0   /*读取SCTLR寄存器，数据保存到r0中*/
    bic r0, r0, #(0x01<<12)     /*清除c1寄存器bit12位(I位)，关闭ICache*/
    bic r0, r0, #(0x01<<11)     /*清除c1寄存器bit11位(Z位)，关闭分支预测*/
    bic r0, r0, #(0x01<<2)      /*清除c1寄存器bit2位(C位)，关闭DCache*/
    bic r0, r0, #0x02           /*清除c1寄存器bit1位(A位)，关闭内存对齐检查*/
    bic r0, r0, #0x01           /*清除c1寄存器bit1位(M位)，关闭MMU*/
    MCR p15, 0, r0, c1, c0, 0

    /*bss段清零*/
    ldr r0, _bss_start
    ldr r1, _bss_end
    mov r2, #0 

bss_loop:
    stmia r0!, {r2} //该汇编指令完成操作后地址递增
    cmp r0, r1
    ble bss_loop

    /*中断向量表地址偏移*/
    ldr r0, =0x87800000
    dsb
    isb
    mcr p15, 0, r0, c12, c0, 0
    dsb
    isb


    /*设置IRQ、SYS、SVC模式下的堆栈指针*/

/*进入IRQ特权模式*/
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x12
    msr cpsr, r0

/*设置栈指针*/
    ldr sp, =0x80600000

/*进入SYS特权模式*/
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x1f
    msr cpsr, r0

/*设置栈指针*/
    ldr sp, =0x80400000

/*进入SVC特权模式*/
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x13
    msr cpsr, r0

/*设置栈指针*/
    ldr sp, =0x80200000

    cpsie i             /*开启IRQ中断*/
    b main


/*未定义指令中断*/
Undefined_Handler:
    ldr r0, =Undefined_Handler
    bx r0

/*SVC中断*/
SVC_Handler:
    ldr r0, =SVC_Handler
    bx r0

/*指令预取中止中断*/
PrefAbort_Handler:
    ldr r0, =PrefAbort_Handler
    bx r0

/*数据访问中止中断*/
DataAbort_Handler:
    ldr r0, =DataAbort_Handler
    bx r0

/*IRQ中断*/
IRQ_Handler:





    

/*FIQ中断*/
FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0



    