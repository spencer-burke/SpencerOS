#include <stdint.h>

extern volatile uint16_t* vga_buffer;

#define VGA_COLS 80
#define VGA_ROWS 25

extern uint8_t term_col;
extern uint8_t term_row;
extern uint8_t term_color;

// Declare methods in terminal.c
void term_init();
void term_putc(char c);
void term_print(const char* str);
