SECTIONS{
    . = 0X87800000;
    .text : {
        obj/start.o
        *(.text)
    }
    .rodata ALIGN(4) : {*(.rodata)}
    .data ALIGN(4) : {*(.data)}
    bss_start = .;
    .bss ALIGN(4) : {*(.bss)}
    bss_end = .;
}