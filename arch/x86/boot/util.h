/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#ifndef UTIL_H
#define UTIL_H


#include <stddef.h>
#include <stdint.h>


// Memory functions
void memset(void* dst, uint8_t val, size_t count);
void memcpy(void* dst, const void* src, size_t count);
void memmove(void* dst, const void* src, size_t count);


// String functions
size_t strlen(const char* str);
char* itoa(int num, char* buffer);


#endif // !UTIL_H