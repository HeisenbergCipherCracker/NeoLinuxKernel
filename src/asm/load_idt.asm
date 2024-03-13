/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
section .text
    global load_idt

load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret