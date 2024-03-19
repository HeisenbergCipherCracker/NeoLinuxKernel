#include <stdint.h>
/*
 * Structure: mp_floating_pointer_structure
 * ----------------------------
 * This will define structure for the concurency of the kernel
 */
struct mp_floating_pointer_structure {
    char signature[4];                 // Signature identifying the structure
    uint32_t configuration_table;      // Address of the configuration table
    uint8_t length;                    // Length of the structure in 16-byte units
    uint8_t mp_specification_revision; // Revision of the MP specification
    uint8_t checksum;                  // Checksum for the structure
    uint8_t default_configuration;     // Flag indicating default configuration presence
    uint32_t features;                 // Features of the configuration
};

struct mp_configuration_table {
    char signature[4]; // "PCMP"
    uint16_t length;
    uint8_t mp_specification_revision;
    uint8_t checksum; // Again, the byte should be all bytes in the table add up to 0
    char oem_id[8];
    char product_id[12];
    uint32_t oem_table;
    uint16_t oem_table_size;
    uint16_t entry_count; // This value represents how many entries are following this table
    uint32_t lapic_address; // This is the memory mapped address of the local APICs 
    uint16_t extended_table_length;
    uint8_t extended_table_checksum;
    uint8_t reserved;
};

 
struct entry_processor {
    uint8_t type; // Always 0
    uint8_t local_apic_id;
    uint8_t local_apic_version;
    uint8_t flags; // If bit 0 is clear then the processor must be ignored
                   // If bit 1 is set then the processor is the bootstrap processor
    uint32_t signature;
    uint32_t feature_flags;
    uint64_t reserved;
};

struct entry_io_apic {
    uint8_t type; // Always 2
    uint8_t id;
    uint8_t version;
    uint8_t flags; // If bit 0 is set then the entry should be ignored
    uint32_t address; // The memory mapped address of the IO APIC is memory
};