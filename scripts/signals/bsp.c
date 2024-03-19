#include  <stdint.h>
#include <stdio.h>
#include <stdlib.h>
volatile uint8_t aprunning = 0;  // count how many APs have started
uint8_t bspid, bspdone = 0;      // BSP id and spinlock flag
// get the BSP's Local APIC ID
__asm__ __volatile__ ("mov $1, %%eax; cpuid; shrl $24, %%ebx;": "=b"(bspid) : : );
 
// copy the AP trampoline code to a fixed address in low conventional memory (to address 0x0800:0x0000)
memcpy((void*)0x8000, &ap_trampoline, 4096);
 
// for each Local APIC ID we do...
for(i = 0; i < numcores; i++) {
	// do not start BSP, that's already running this code
	if(lapic_ids[i] == bspid) continue;
	// send INIT IPI
	*((volatile uint32_t*)(lapic_ptr + 0x280)) = 0;                                                                             // clear APIC errors
	*((volatile uint32_t*)(lapic_ptr + 0x310)) = (*((volatile uint32_t*)(lapic_ptr + 0x310)) & 0x00ffffff) | (i << 24);         // select AP
	*((volatile uint32_t*)(lapic_ptr + 0x300)) = (*((volatile uint32_t*)(lapic_ptr + 0x300)) & 0xfff00000) | 0x00C500;          // trigger INIT IPI
	do { __asm__ __volatile__ ("pause" : : : "memory"); }while(*((volatile uint32_t*)(lapic_ptr + 0x300)) & (1 << 12));         // wait for delivery
	*((volatile uint32_t*)(lapic_ptr + 0x310)) = (*((volatile uint32_t*)(lapic_ptr + 0x310)) & 0x00ffffff) | (i << 24);         // select AP
	*((volatile uint32_t*)(lapic_ptr + 0x300)) = (*((volatile uint32_t*)(lapic_ptr + 0x300)) & 0xfff00000) | 0x008500;          // deassert
	do { __asm__ __volatile__ ("pause" : : : "memory"); }while(*((volatile uint32_t*)(lapic_ptr + 0x300)) & (1 << 12));         // wait for delivery
	mdelay(10);                                                                                                                 // wait 10 msec
	// send STARTUP IPI (twice)
	for(j = 0; j < 2; j++) {
		*((volatile uint32_t*)(lapic_ptr + 0x280)) = 0;                                                                     // clear APIC errors
		*((volatile uint32_t*)(lapic_ptr + 0x310)) = (*((volatile uint32_t*)(lapic_ptr + 0x310)) & 0x00ffffff) | (i << 24); // select AP
		*((volatile uint32_t*)(lapic_ptr + 0x300)) = (*((volatile uint32_t*)(lapic_ptr + 0x300)) & 0xfff0f800) | 0x000608;  // trigger STARTUP IPI for 0800:0000
		udelay(200);                                                                                                        // wait 200 usec
		do { __asm__ __volatile__ ("pause" : : : "memory"); }while(*((volatile uint32_t*)(lapic_ptr + 0x300)) & (1 << 12)); // wait for delivery
	}
}
// release the AP spinlocks
bspdone = 1;
// now you'll have the number of running APs in 'aprunning'