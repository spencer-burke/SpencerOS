#include "keyboard.h"
#include "terminal.h"
#include "pic.h"
#include <stdint.h>

// Define the PS/2 scancode set 1 (index is the scancode value is the character)
// The 0 means no printable character (shift, enter, ctrl, etc.)
static const char scancode_table[128] = {
    0,    0,   '1', '2', '3', '4', '5', '6', '7', '8',  // 0x00-0x09
    '9', '0', '-', '=',  0,    0,  'q', 'w', 'e', 'r',  // 0x0A-0x13
    't', 'y', 'u', 'i', 'o', 'p', '[', ']',  0,    0,   // 0x14-0x1D
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',  // 0x1E-0x27
    '\'','`',  0,  '\\','z', 'x', 'c', 'v', 'b', 'n',  // 0x28-0x31
    'm', ',', '.', '/',  0,   '*',  0,  ' ',             // 0x32-0x39
};

// Keyboard handler for when IRQ1 fires
void keyboard_handler()
{
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);

    // Bit 7 means key release so ignore it
    if (scancode & 0x80) {
        outb(PIC_MASTER_CMD, PIC_EOI);
        return;
    }

    // Look up scancode
    if (scancode < 128 && scancode_table[scancode] != 0) {
        char key[2] = { scancode_table[scancode], '\0' };
        term_print("Key pressed: ");
        term_print(key);
        term_print("\n");
    }

    // Send EOI to master PIC so it knows we handled IRQ1
    outb(PIC_MASTER_CMD, PIC_EOI);
}

