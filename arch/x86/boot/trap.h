/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#ifndef TRAP_H
#define TRAP_H


void trap_vectors_init();
void idt_init();
void pic_init();
void pic_enable(int irq);


#endif // !TRAP_H