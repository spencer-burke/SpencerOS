// Include the headers for standard numbers as they are needed to describe the table
#include <stdint.h>

// Define and pack a single entry in the gdt
typedef struct gdt_entry
{
    // It has these fields to match the processor, not the logical layout shown in most diagrams
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t limit_high_flags;
    uint8_t base_high;
} __attribute__ ((packed)) gdt_entry;

// Define and pack a named version of the full table
typedef struct gdt
{
    gdt_entry null;
    gdt_entry kernel_code;
    gdt_entry kernel_data;
    gdt_entry user_code;
    gdt_entry user_data;
} __attribute__ ((packed)) gdt_table;
