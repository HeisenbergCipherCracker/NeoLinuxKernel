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