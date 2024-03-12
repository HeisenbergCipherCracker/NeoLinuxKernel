#ifndef ARCH_H
#define ARCH_H

void gdt_entry();
void init_gdt();
void init_idt();
void arch_init();

#endif // ARCH_H