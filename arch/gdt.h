#ifndef GDT_H
#define GDT_H

// Include the headers for standard numbers as they are needed to describe the table
#include <stdint.h>

// Individual bits
#define GDT_PRESENT (1 << 7)   // segment is valid, must be 1
#define GDT_RING0 (0 << 5)   // kernel privilege level
#define GDT_RING3 (3 << 5)   // user privilege level
#define GDT_DESCRIPTOR (1 << 4)   // code or data segment (not system)
#define GDT_EXECUTABLE (1 << 3)   // code segment if set, data if not
#define GDT_READWRITE (1 << 1)   // readable (code) or writable (data)

// Flags nibble
#define GDT_GRANULARITY (1 << 3)   // limit is in 4K blocks not bytes
#define GDT_32BIT (1 << 2)   // 32 bit protected mode segment

// Prebuilt access bytes for each segment type
#define GDT_ACCESS_KERNEL_CODE (GDT_PRESENT | GDT_RING0 | GDT_DESCRIPTOR | GDT_EXECUTABLE | GDT_READWRITE)
#define GDT_ACCESS_KERNEL_DATA (GDT_PRESENT | GDT_RING0 | GDT_DESCRIPTOR | GDT_READWRITE)
#define GDT_ACCESS_USER_CODE (GDT_PRESENT | GDT_RING3 | GDT_DESCRIPTOR | GDT_EXECUTABLE | GDT_READWRITE)
#define GDT_ACCESS_USER_DATA (GDT_PRESENT | GDT_RING3 | GDT_DESCRIPTOR | GDT_READWRITE)

// Prebuilt flags
#define GDT_FLAGS (GDT_GRANULARITY | GDT_32BIT)

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

// Define and pack the pointer for the lgdt instruction
typedef struct gdt_ptr_t
{
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed)) gdt_ptr_t;

// Declare the assembly function from gdt.s
extern void gdt_load(gdt_ptr_t *ptr);

// Declare functions in gdt.c
void gdt_set_entry(gdt_entry *entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void gdt_init();

#endif
