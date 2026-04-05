#include "pic.h"
#include <stdint.h>

// Initialize the pic
void pic_init()
{
    /////// ICW1 tell both PICs to start initialization
    /////outb(PIC_MASTER_CMD, ICW1_INIT | ICW1_ICW4); io_wait();
    /////outb(PIC_SLAVE_CMD, ICW1_INIT | ICW1_ICW4); io_wait();

    /////// ICW2 set vector offsets (master starts at 32, slave at 40)
    /////outb(PIC_MASTER_DATA, 32); io_wait();
    /////outb(PIC_SLAVE_DATA, 40); io_wait();

    /////// ICW3 tell master/slave how they are wired together
    /////outb(PIC_MASTER_DATA, 0x04); io_wait(); // master is on IRQ2 (bit 2)
    /////outb(PIC_SLAVE_DATA, 0x02); io_wait(); // slave its cascade identity is 2

    /////// ICW4 set 8086 mode on both
    /////outb(PIC_MASTER_DATA, ICW4_8086); io_wait();
    /////outb(PIC_SLAVE_DATA, ICW4_8086); io_wait();

    /////// Unmask all IRQs on both PICs (0x00 = all enabled)
    /////outb(PIC_MASTER_DATA, 0x00);
    /////outb(PIC_SLAVE_DATA, 0x00);

    // ICW1
    outb(PIC_MASTER_CMD, ICW1_INIT | ICW1_ICW4);
    outb(PIC_SLAVE_CMD,  ICW1_INIT | ICW1_ICW4);
    // ICW2 - vector offsets
    outb(PIC_MASTER_DATA, 0x20);  // master starts at 32
    outb(PIC_SLAVE_DATA,  0x28);  // slave starts at 40
    // ICW3 - wiring
    outb(PIC_MASTER_DATA, 0x04);  // master has slave on IRQ2
    outb(PIC_SLAVE_DATA,  0x02);  // slave cascade identity
    // ICW4
    outb(PIC_MASTER_DATA, ICW4_8086);
    outb(PIC_SLAVE_DATA,  ICW4_8086);
    // unmask all
    outb(PIC_MASTER_DATA, 0x00);
    outb(PIC_SLAVE_DATA,  0x00);
}
