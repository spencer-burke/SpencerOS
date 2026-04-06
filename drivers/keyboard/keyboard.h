#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_DATA_PORT 0x60

// Declare functions in keyboard.c
void keyboard_init();
void keyboard_handler();

#endif
