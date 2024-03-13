/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#ifndef ARCH_H
#define ARCH_H

void gdt_entry();
void init_gdt();
void init_idt();
void arch_init();

#endif // ARCH_H