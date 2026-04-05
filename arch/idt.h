#include <stdint.h>

// Total number of idt entries (one per interrupt vector)
#define IDT_ENTRIES 256

// Type/attribute bits (access byte)
#define IDT_PRESENT (1 << 7) // entry is valid
#define IDT_RING0 (0 << 5) // kernel privelege
#define IDT_RING3 (3 << 5) // user privelege (e.g. syscall gate)

// Gate types (lower nibble of attribute byte)
#define IDT_TASK_GATE 0x5
#define IDT_INT_GATE 0xE
#define IDT_TRAP_GATE 0xF

// Prebuilt attribute bytes for common cases
#define IDT_ATTR_KERNEL_INT (IDT_PRESENT | IDT_RING0 | IDT_INT_GATE)
#define IDT_ATTR_KERNEL_TRAP (IDT_PRESENT | IDT_RING0 | IDT_TRAP_GATE)
#define IDT_ATTR_USER_INT    (IDT_PRESENT | IDT_RING3 | IDT_INT_GATE)

// Define and pack a single entry in the idt
typedef struct idt_entry
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attributes;
    uint16_t offset_high;
} __attribute__ ((packed)) idt_entry;

// Define and pack the named version of the full table
typedef struct idt
{
    idt_entry entries[IDT_ENTRIES];
} __attribute__ ((packed)) idt_table;

// Define and pack the pointer for the lidt instruction
typedef struct idt_ptr_t
{
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed)) idt_ptr_t;

// Declare the assembly function from idt.s
extern void idt_load(idt_ptr_t *ptr);

// Declare the assembly function from keyboard.h
extern void keyboard_isr();

// Declare functions in idt.c
void pic_init();
void idt_set_entry(uint8_t entry, uint32_t handler, uint16_t selector, uint8_t attributes);
void idt_init();
