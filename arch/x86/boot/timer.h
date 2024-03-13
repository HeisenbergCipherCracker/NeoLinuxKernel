/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#ifndef TIMER_H
#define TIMER_H


#define TIMER_TPS 100

extern volatile uint64_t ticks;					// "volatile" hints the C compiler that this global variable may be updated from other place (i.e. interrupt / IRQ 0), so don't optimize

void timer_init();


#endif // !TIMER_H