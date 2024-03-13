/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#include "math.h"


float64_t sin(float64_t x) {
	float64_t result;
	asm("fsin" : "=t"(result) : "0"(x));
	return result;
}

float64_t cos(float64_t x) {
	return sin(x + PI / 2.0);
}


static uint32_t rseed = 1;

void seed(uint32_t s) {
	rseed = s;
}

uint32_t rand() {
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;

	x *= 23786259 - rseed;

	uint32_t t;

	t = x ^ (x << 11);
	x = y; y = z; z = w;
	w = w ^ (w >> 19) ^ t ^ (t >> 8);

	return w;
}