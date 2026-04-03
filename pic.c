#include "pic.h"
#include <stdint.h>

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

// Initialize the pic
void pic_init()
{
    // ICW1 tell both PICs to start initialization
    outb(PIC_MASTER_CMD, ICW1_INIT | ICW1_ICW4); io_wait();
    outb(PIC_SLAVE_CMD, ICW1_INIT | ICW1_ICW4); io_wait();

    // ICW2 set vector offsets (master starts at 32, slave at 40)
    outb(PIC_MASTER_DATA, 32); io_wait();
    outb(PIC_SLAVE_DATA, 40); io_wait();

    // ICW3 tell master/slave how they are wired together
    outb(PIC_MASTER_DATA, 0x04); io_wait(); // master is on IRQ2 (bit 2)
    outb(PIC_SLAVE_DATA, 0x02); io_wait(); // slave its cascade identity is 2

    // ICW4 set 8086 mode on both
    outb(PIC_MASTER_DATA, ICW4_8086); io_wait();
    outb(PIC_SLAVE_DATA, ICW4_8086); io_wait();

    // Unmask all IRQs on both PICs (0x00 = all enabled)
    outb(PIC_MASTER_DATA, 0x00);
    outb(PIC_SLAVE_DATA, 0x00);
}
