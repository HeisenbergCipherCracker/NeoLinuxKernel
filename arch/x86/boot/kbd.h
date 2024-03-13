/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#ifndef KBD_H
#define KBD_H


#include <stdbool.h>


void kbd_init();
void kbd_intr();
bool kbhit();
char getch();


#endif // !KBD_H