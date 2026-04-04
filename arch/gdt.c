#include "gdt.h"
#include <stdint.h>

gdt_table gdt;
gdt_ptr_t gdt_ptr;

// Set the values of a single entry in the gdt
void gdt_set_entry(gdt_entry *entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    /*
     * base is 32 bits -> split across base_low (16), base_mid (8), base_high (8)
     * limit is 20 bits -> split across limit_low (16) and top nibble of limit_high_flags (4)
     * flags is 4 bits  -> packed into top nibble of limit_high_flags
     * ((limit >> 16) & 0x0F)  -> grab bits 19:16 of limit
     * | (flags << 4)          -> shift flags into top nibble
     */
    entry->base_low = base & 0xFFFF;
    entry->base_mid = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24) & 0xFF;
    entry->limit_low = limit & 0xFFFF;
    entry->limit_high_flags = ((limit >> 16) & 0x0F) | (flags << 4);
    entry->access = access;
}

// Set all values in the gdt
void gdt_init()
{
    // Set up gdt pointer for lgdt
    gdt_ptr.limit = sizeof(gdt_table) - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    // Set null descriptor
    gdt_set_entry(&gdt.null, 0, 0, 0, 0);

    // Set kernel segments
    gdt_set_entry(&gdt.kernel_code, 0, 0xFFFFF, GDT_ACCESS_KERNEL_CODE, GDT_FLAGS);
    gdt_set_entry(&gdt.kernel_data, 0, 0xFFFFF, GDT_ACCESS_KERNEL_DATA, GDT_FLAGS);

    // Set user segments
    gdt_set_entry(&gdt.user_code, 0, 0xFFFFF, GDT_ACCESS_USER_CODE, GDT_FLAGS);
    gdt_set_entry(&gdt.user_data, 0, 0xFFFFF, GDT_ACCESS_USER_DATA, GDT_FLAGS);

    // Make assembly load the gdt
    gdt_load(&gdt_ptr);
}
