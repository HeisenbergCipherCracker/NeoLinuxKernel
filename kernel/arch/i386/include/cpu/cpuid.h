#ifndef _X86_CPUID_H
#define _X86_CPUID_H

#include <core/system.h>

union x86_cpuid_vendor {
    char string[13];
    uint32_t array[3];
} __packed;

#if 0
struct x86_cpuid_features {
    int fpu   : 1;  /* onboard x87 FPU */
    int vme   : 1;  /* Virtual 8086 Mode Extensions */
    int de    : 1;  /* Debugging Extensions */
    int pse   : 1;  /* Page Size Extensions */
    int tsc   : 1;  /* Time Stamp Counter */
    int msr   : 1;  /* Mode Specific Regisgers */
    int pae   : 1;  /* Physical Address Extensions */
    int mce   : 1;  /* Machine Check Exceptions */
    int cx8   : 1;  /* CMPXCHG8 (compare and swap) instruction support */
    int apic  : 1;  /* onboard Advanced Programmable Interrupt Controller */
    int       : 1;  /* reserved */
    int sep   : 1;  /* SYSENTER and SYSEXIT instructions */
    int mtrr  : 1;  /* Memory Type Range Registers */
    int pge   : 1;  /* Page Global Enable bit in CR4 support */
    int mca   : 1;  /* Machine Check Architecture */
    int cmov  : 1;  /* Conditional MOV and FCMOV instructions support */
    int pat   : 1;  /* Page Attribute Table */
    int pse36 : 1;  /* 36-bit Page Size Extension */
    int psn   : 1;  /* Processor Serial Number */
    int clfsh : 1;  /* CLFluSH instruction (SSE2) support */
    int       : 1;  /* reserved */
    int ds    : 1;  /* Debug Store: save trace of executed jumps */
    int acpi  : 1;  /* onboard thermal contorl MSRs for ACPI */
    int mmx   : 1;  /* MMX instructions support */
    int fxsr  : 1;  /* FXSAVE, FXRESTOR instruction support */
    int sse   : 1;  /* SSE instruction support */
    int sse2  : 1;  /* SSE2 instruction support */
    int ss    : 1;  /* CPU cache Self-Snoop support */
    int htt   : 1;  /* Hyper-Threading Technology support */
    int tm    : 1;  /* Thermal Monitor support */
    int ia64  : 1;  /* IA64 processor emulating x86 */
    int pbe   : 1;  /* Pending Break Enable */
} __packed;

int x86_cpuid_check(void);

static inline int x86_cpuid_features(struct x86_cpuid_features *features)
{
    if (x86_cpuid_check()) {
        asm volatile ("cpuid":"=b"((int){0}), "=c"((int){0}), "=d"(*features):"a"(1):"memory");
    } else {
        /* CPUID is not supported -- fall back to i386 */
        /* TODO */
        printk("i386 Support not implemented");
        for (;;);
    }

    return 0;
}
#endif

static inline int x86_cpuid_vendor(union x86_cpuid_vendor *vendor)
{
    asm volatile("cpuid":
        "=b"(vendor->array[0]),
        "=d"(vendor->array[1]),
        "=c"(vendor->array[2])
        :"a"(0));
    vendor->string[12] = 0;
    return 0;
}

#endif
