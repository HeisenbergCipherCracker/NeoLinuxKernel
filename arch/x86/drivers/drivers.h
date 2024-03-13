/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
// Define the base address of the keyboard hardware
#define KEYBOARD_BASE_ADDRESS 0x1234

// Define the keyboard registers
#define KEYBOARD_STATUS_REG (KEYBOARD_BASE_ADDRESS + 0)
#define KEYBOARD_DATA_REG (KEYBOARD_BASE_ADDRESS + 1)

// Define keyboard status bits
#define KEYBOARD_STATUS_BIT_DATA_READY (1 << 0)

// Read a byte from the specified port
static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

// Write a byte to the specified port
static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile("outb %0, %1" ::"a"(value), "Nd"(port));
}

// Initialize the keyboard driver
void keyboard_init() {
    // Nothing to initialize for this simple example
}

// Check if there is data available from the keyboard
bool keyboard_has_data() {
    return (inb(KEYBOARD_STATUS_REG) & KEYBOARD_STATUS_BIT_DATA_READY) != 0;
}

// Read a character from the keyboard
char keyboard_read_char() {
    return inb(KEYBOARD_DATA_REG);
}

int main() {
    keyboard_init();

    while (true) {
        if (keyboard_has_data()) {
            char c = keyboard_read_char();

            // Example: convert lowercase letters to uppercase
            if (islower(c)) {
                c = toupper(c);
            }

            // Example: echo the character
            putchar(c);
        }
    }

    return 0;
}
