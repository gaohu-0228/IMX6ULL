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
    ldr pc, =NotUsed_Handler    /*未使用的中断*/
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
    mcr p15, 0, r0, c1, c0, 0   /*将r0的值写入到cp15的c1中*/

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

/*未使用的中断*/
NotUsed_Handler:
    ldr r0, =NotUsed_Handler
    bx r0

/*IRQ中断*/
IRQ_Handler:
    push {lr}           /*保存lr地址*/
    push {r0-r2, r12}   /*保存r0-r3, r12寄存器*/

    mrs r0, spsr        /*读取SPSR寄存器*/
    push {r0}           /*保存SPSR寄存器*/

    //MRC p15, 4, <Rt>, c15, c0, 0; Read Configuration Base Address Register
    mcr p15, 4, r1, c15, c0, 0  /*将CP15的C0内的值读取到R1寄存器中*/

    add r1, r1, #0x2000         /*GIC控制器基地址加上0x2000, 得到CPU接口端基地址*/
    ldr r0, [r1, #0x000C]       /*CPU接口端基地址加上0x000C, 得到GICC_IAR寄存器*/

    push {r0, r1}               /*保存r0, r1*/

    cps #0x13                   /*在特权模式下, 把cpsr寄存器的m[4:0]修改为0x13, 让处理器进入svc模式*/

    push {lr}                   /*保存svc模式下的lr寄存器*/

    ldr r2, =system_irqhandler  /*将c语言中断处理函数的地址加载到r2寄存器中*/
    blx r2                      /*跳转到c语言中断处理函数, 带有一个参数， 保存到r0寄存器中*/

    pop {lr}                    /*执行完c语言中断处理函数, lr出栈*/
    cps #0x12                   /*进入irq模式*/
    pop {r0, r1}                /*寄存器r0, r1出栈*/
    str r0, [r1, #0x10]         /*中断执行完成后, 将r0的值写入到GICC_EOIR中*/

    pop {r0}                    /*寄存器r0出栈*/
    msr spsr_cxsf, r0           /*回复spsr状态*/
    pop {r0-r3, r12}            /*寄存器r0-r3, r12出栈*/
    pop {r12}                   /*寄存器lr出栈*/
    subs pc, lr, #0x04          /*将寄存器lr中的值-4然后保存到pc中*/

/*FIQ中断*/
FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0



    