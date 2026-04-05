#include "idt.h"
#include "terminal.h"
#include <stdint.h>

idt_table idt;
idt_ptr_t idt_ptr;

// Set the values of a single entry in the idt
void idt_set_entry(uint8_t entry, uint32_t handler, uint16_t selector, uint8_t attributes)
{
    /*
     * handler is 32 bits split across offset_low (16) and offset_high (16)
     * selector is the kernel code segment (typically 0x08)
     * zero is just zero
     * type_attributes hold the gate type, DPL, and present bit
     */
    idt.entries[entry].offset_low = handler & 0xFFFF;
    idt.entries[entry].offset_high = (handler >> 16) & 0xFFFF;
    idt.entries[entry].selector = selector;
    idt.entries[entry].zero = 0;
    idt.entries[entry].type_attributes = attributes;
}

// Set all values in the idt (currently implemented)
void idt_init()
{

    // Set up the idt pointer for lidt
    idt_ptr.limit = sizeof(idt_table) - 1;
    idt_ptr.base = (uint32_t)&idt;

    // Set up any interrupt handlers as they are implemented
    idt_set_entry(9, (uint32_t)keyboard_isr, 0x08, IDT_ATTR_KERNEL_INT);   // old vector
    idt_set_entry(33, (uint32_t)keyboard_isr, 0x08, IDT_ATTR_KERNEL_INT);

    // Make assembly load the idt
    idt_load(&idt_ptr);
}
