#include <stdio.h>
#include <stdint.h>

// Define TLB entry structure
struct tlb_entry {
    uint32_t virtual_address;
    uint32_t physical_address;
    uint8_t valid;
};

// Define TLB array
#define TLB_SIZE 16
struct tlb_entry tlb[TLB_SIZE];

/**
 * Function: hw_tlb
 * ----------------------------
 * Performs address translation using a hardware-managed TLB.
 *
 * Parameters:
 *     virtual_address: The virtual address to be translated.
 *
 * Returns:
 *     The corresponding physical address if translation is successful,
 *     otherwise returns -1 to indicate translation failure.
 */
int hw_tlb(uint32_t virtual_address) {
    // Iterate through TLB entries to search for a match
    for (int i = 0; i < TLB_SIZE; i++) {
        // Check if the entry is valid and the virtual address matches
        if (tlb[i].valid && tlb[i].virtual_address == virtual_address) {
            // TLB hit, return the corresponding physical address
            return tlb[i].physical_address;
        }
    }
    // TLB miss
    return -1;
}

/**
 * Function: add_tlb_entry
 * ----------------------------
 * Adds an entry to the TLB.
 *
 * Parameters:
 *     virtual_address: The virtual address.
 *     physical_address: The corresponding physical address.
 */
void add_tlb_entry(uint32_t virtual_address, uint32_t physical_address) {
    // Iterate through TLB entries to find an empty slot
    for (int i = 0; i < TLB_SIZE; i++) {
        // Check for an empty slot
        if (!tlb[i].valid) {
            // Add the new TLB entry
            tlb[i].virtual_address = virtual_address;
            tlb[i].physical_address = physical_address;
            tlb[i].valid = 1; // Mark the entry as valid
            return;
        }
    }
    // TLB is full, perform replacement policy (e.g., FIFO or LRU)
    // For simplicity, FIFO replacement is used here
    // Replace the oldest entry (the one at index 0)
    tlb[0].virtual_address = virtual_address;
    tlb[0].physical_address = physical_address;
    tlb[0].valid = 1; // Mark the entry as valid
}

int main() {
    // Example usage of hw_tlb and add_tlb_entry functions
    // Assume virtual and physical addresses are 32-bit integers

    // Add some TLB entries (for demonstration purposes)
    add_tlb_entry(0x12345678, 0xABCDEF00);
    add_tlb_entry(0x87654321, 0xFEDCBA01);

    // Perform address translation using TLB
    uint32_t virtual_addr = 0x12345678;
    int physical_addr = hw_tlb(virtual_addr);
    if (physical_addr != -1) {
        // Translation successful
        printf("Physical address for virtual address 0x%x: 0x%x\n", virtual_addr, physical_addr);
    } else {
        // Translation failed (TLB miss)
        printf("Translation failed for virtual address 0x%x\n", virtual_addr);
    }

    return 0;
}
