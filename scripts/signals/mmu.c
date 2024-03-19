#include <stdint.h>
// Abstract model of a TLB.
 
typedef uintptr_t vaddr_t;
typedef uintptr_t paddr_t;
 
// Flag to mark an entry in the modelled hardware TLB as having been set for use as a valid translation.
#define TLB_ENTRY_FLAGS_INUSE
#define CPU_MODEL_MAX_TLB_ENTRIES  16 // Maximum number of entries that can be supported by this model.
                                     // This is not necessarily the maximum number of entries that could actually exist on any
 
struct tlb_cache_record_t
{
   vaddr_t entry_virtual_address;
   paddr_t relevant_physical_address;
   uint16_t permissions;
};
 
// Instance of a hardware Translation Lookaside Buffer.
struct tlb_cache_record_t   hw_tlb[CPU_MODEL_MAX_TLB_ENTRIES];
