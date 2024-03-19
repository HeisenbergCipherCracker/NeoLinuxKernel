#include "pics.h" // Include custom PIC definitions header
#include <stdio.h>
#include <stdint.h>

/*
 * This section contains functions and definitions related to the 8259 Programmable Interrupt Controller (PIC).
 */

// Define the End-of-Interrupt command code
#define PIC_EOI 0x20
#define ICW4_8086 0x01    /* 8086/88 (MCS-80/85) mode */


// Define port addresses and commands for PICs
#define PIC1 0x20 // IO base address for master PIC
#define PIC2 0xA0 // IO base address for slave PIC
#define ICW1_INIT 0x10       /* Initialization - required! */
#define ICW1_ICW4 0x01       /* ICW4 (not) needed */
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

// Function prototypes for low-level I/O operations
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
void io_wait();

/*
 * Function: outb
 * ----------------------------
 * Sends a byte to a specified I/O port.
 *
 * port: The I/O port address.
 * value: The value to be written.
 */
void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

/*
 * Function: inb
 * ----------------------------
 * Reads a byte from a specified I/O port.
 *
 * port: The I/O port address.
 *
 * returns: The value read from the port.
 */
uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/*
 * Function: io_wait
 * ----------------------------
 * Waits for an I/O operation to complete.
 * This is achieved by sending a dummy read to an unused I/O port.
 */
void io_wait() {
    asm volatile ("outb %%al, $0x80" : : "a"(0));
}

/*
 * Function: PIC_sendEOI
 * ----------------------------
 * Sends the End-of-Interrupt (EOI) command to the PIC(s) for the specified IRQ.
 *
 * irq: The IRQ for which EOI is to be sent.
 */
void PIC_sendEOI(uint8_t irq) {
    if (irq >= 8)
        outb(PIC2_COMMAND, PIC_EOI); // Send EOI to slave PIC if necessary
    outb(PIC1_COMMAND, PIC_EOI); // Send EOI to master PIC
}

/*
 * Function: PIC_remap
 * ----------------------------
 * Initializes the PIC by remapping its vectors.
 *
 * offset1: Vector offset for master PIC.
 * offset2: Vector offset for slave PIC.
 */
void PIC_remap(int offset1, int offset2) {
    uint8_t a1, a2;
 
    // Save current masks
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);
 
    // Start initialization sequence
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
 
    // Set vector offsets
    outb(PIC1_DATA, offset1);
    io_wait();
    outb(PIC2_DATA, offset2);
    io_wait();
 
    // Configure PIC cascading
    outb(PIC1_DATA, 4); // Tell master PIC about slave PIC at IRQ2
    io_wait();
    outb(PIC2_DATA, 2); // Tell slave PIC its cascade identity
    io_wait();
 
    // Configure PIC mode (8086 mode)
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();
 
    // Restore saved masks
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}

/*
 * Function: pic_disable
 * ----------------------------
 * Disables all interrupts from both PICs.
 */
void pic_disable(void) {
    outb(PIC1_DATA, 0xFF); // Mask all interrupts on master PIC
    outb(PIC2_DATA, 0xFF); // Mask all interrupts on slave PIC
}

/*
 * Function: IRQ_set_mask
 * ----------------------------
 * Sets the interrupt mask for the specified IRQ line.
 *
 * IRQline: The IRQ line to set the mask for.
 */
void IRQ_set_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;
 
    if (IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
 
    // Set the mask bit for the specified IRQ line
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}

/*
 * Function: IRQ_clear_mask
 * ----------------------------
 * Clears the interrupt mask for the specified IRQ line.
 *
 * IRQline: The IRQ line to clear the mask for.
 */
void IRQ_clear_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;
 
    if (IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
 
    // Clear the mask bit for the specified IRQ line
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}
