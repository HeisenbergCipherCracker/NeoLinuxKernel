/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#include "panic.h"
#include "console.h"

void panic(char *message){
    printf("\nKernel Panic! System Halting\nReason: %s\n", message);
    asm volatile("hlt");
}