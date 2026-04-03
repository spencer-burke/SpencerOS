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

// Declare the functions in the pic.c
static inline void outb(uint16_t port, uint8_t value);
static inline void io_wait();
void pic_init();
