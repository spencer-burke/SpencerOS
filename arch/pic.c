#include "pic.h"
#include <stdint.h>

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

    // Unmask IRQ1 on master and mask everything on slave
    // 11111101 - only unmask IRQ1
    outb(PIC_MASTER_DATA, 0xFD);
    // mask everything on slave
    outb(PIC_SLAVE_DATA, 0xFF);
}
