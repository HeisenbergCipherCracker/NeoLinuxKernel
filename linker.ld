ENTRY(kernel_entry)

SECTIONS {
    . = 0x100000;  /* Kernel entry point address */
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }
}
