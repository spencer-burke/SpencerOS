#ifndef PIC_H
#define PIC_H

#include <stdint.h>

#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD 0xA0
#define PIC_SLAVE_DATA 0xA1

#define PIC_EOI 0x20 // end of interrupt signal

// ICW1 start initialization sequence
#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01 // ICW4 still needed

// ICW4 set 8086 mode
#define ICW4_8086 0x01

// Helper to write a byte to an I/O port
static inline void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Helper to create a small delay via a throwaway I/O write (port 0x80 is safe for this)
static inline void io_wait()
{
    __asm__ volatile ("outb %0, $0x80" : : "a"((uint8_t)0));
}

// Helper to read a byte from an I/O port
static inline uint8_t inb(uint16_t port)
{
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

// Helper to call the sti instruction to enable interrupts (for the hardware drivers) 
static inline void sti_enable()
{
    __asm__ volatile ("sti");
}

// Declare the function in the pic.c
void pic_init();

#endif
