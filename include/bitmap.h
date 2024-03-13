/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#ifndef BITMAP_H
#define BITMAP_H

#include "types.h"

#define BITMAP_SIZE 8

void bitmap_draw_char(char ch, int x, int y, int color);

void bitmap_draw_string(const char *str, int x, int y, int color);

#endif