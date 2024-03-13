/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#ifndef BOOT_BOOT_H
#define BOOT_BOOT_H
/*Useful macros*/
#define STACK_SIZE	1024	/* Minimum number of bytes for stack */


#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

extern struct setup_header hdr;
extern struct boot_params boot_params;

#define cpu_relax()	asm volatile("rep; nop")

static inline void io_delay(void){
    const u16 DELAY_PORT = 0x80;
    outb(0, DELAY_PORT)
}

#endif // BOOT_BOOT_H