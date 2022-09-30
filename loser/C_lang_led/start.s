.global _start
/*
* SP 堆栈指针
* LR 链接寄存器
* PC 程序寄存器
* CPSR 当前程序状态寄存器
* SPSR 备份程序状态寄存器
*/
_start:
    mrs r0, cpsr // 进入SVC特权模式
    bic r0, r0, #0x1F // 将r0的低5位清0
    orr r0, r0, #0x13 // r0或上0x13，表示使用svc模式
    msr cpsr, r0 // 将r0的数据写入cpsr中

    ldr sp, =0x80200000 // 设置栈指针

    b main // 跳转到main函数
