/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#include <stdint.h>
void x86Init() {
    // PIC initialization
    __asm__ volatile("mov $0x20, %al; outb %al, $0x20; outb %al, $0xA0");
    __asm__ volatile("mov $0x21, %al; mov $0x00, %ah; outb %al, $0x21");
    __asm__ volatile("mov $0xA1, %al; mov $0x00, %ah; outb %al, $0xA1");

    // PIT initialization
    __asm__ volatile("mov $0x34, %al; mov $0x43, %dx; outb %al, %dx");
    __asm__ volatile("mov $0x9C, %al; outb %al, $0x40");
    __asm__ volatile("mov $0x2E, %al; outb %al, $0x40");
}
