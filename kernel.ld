ENTRY(kernel_entry)

SECTIONS {
    . = 1M; /* Start the kernel at 1MB */

    .text ALIGN (0x1000) : {
        *(.text)
    }

    .rodata ALIGN (0x1000) : {
        *(.rodata)
    }

    .data ALIGN (0x1000) : {
        *(.data)
    }

    .bss ALIGN (0x1000) : {
        *(.bss)
    }

    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
    }
}
