/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#ifndef UTILS_H
#define UTILS_H

#include "types.h"

#define TRUE  1
#define FALSE 0

extern uint32 strlen(const char*);
extern uint32 digit_count(int);
extern void itoa(int, char *);

#endif

