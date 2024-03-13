/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
// arch/arch.c
#include <stdint.h>

// Struct for a GDT entry
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

// Struct for the GDT pointer
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Global Descriptor Table (GDT) initialization
void init_gdt() {
    // Define GDT entries (e.g., null segment, code segment, data segment)
    struct gdt_entry gdt[3];
    gdt[0] = (struct gdt_entry){0}; // Null segment
    gdt[1] = (struct gdt_entry){
        .limit_low = 0xFFFF,
        .base_low = 0,
        .base_middle = 0,
        .access = 0x9A,
        .granularity = 0xCF,
        .base_high = 0
    }; // Code segment
    gdt[2] = (struct gdt_entry){
        .limit_low = 0xFFFF,
        .base_low = 0,
        .base_middle = 0,
        .access = 0x92,
        .granularity = 0xCF,
        .base_high = 0
    }; // Data segment

    // Load GDT
    struct gdt_ptr gp;
    gp.limit = sizeof(gdt) - 1;
    gp.base = (uint32_t)&gdt;

    __asm__ volatile("lgdt %0" : : "m"(gp));
}

// Initialize Interrupt Descriptor Table (IDT)
void init_idt() {
    // IDT initialization code
}

// Architecture-specific initialization
void arch_init() {
    // Disable interrupts
    __asm__ volatile("cli");

    // Initialize GDT
    init_gdt();

    // Initialize IDT
    init_idt();

    // Enable interrupts
    __asm__ volatile("sti");
}
