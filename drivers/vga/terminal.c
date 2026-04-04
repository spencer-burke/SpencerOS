#include "terminal.h"
#include <stdint.h>
#include <stddef.h>

// This is x86's VGA textmode buffer.
// To display text, we write data to this memory location
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

// We start displaying text in the top-left of the screen
// (column = 0, row = 0)
uint8_t term_col = 0;
uint8_t term_row = 0;
// Black background, white foreground
uint8_t term_color = 0x0F;

// This function initiates the terminal by clearing it
void term_init()
{
    for (int col = 0; col < VGA_COLS; col++) {
        for (int row = 0; row < VGA_ROWS; row++) {
            // Calculate buffer index for character
            const size_t index = (VGA_COLS * row) + col;
            // Set the character to blank (a space character)
            vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
        }
    }
}

void term_putc(char c)
{
    switch(c) {
        // Newline characters should return the column to 0, and increment the row
        case '\n': {
            term_col = 0;
            term_row++;
            break;
        }
        // Normal characters just get displayed  and then increment the column
        default: {
            // Calculate buffer index for character
            const size_t index = (VGA_COLS * term_row) + term_col;
            vga_buffer[index] = ((uint16_t)term_color << 8) | c;
            term_col++;
            break;
        }
    }

    // If it gets past the column, reset it, and increment the row to get a new line
    if (term_col >= VGA_COLS) {
        term_col = 0;
        term_row++;
    }

    // If it gets pas the last row, reset both the column and row to 0 in order to loop back to the top
    if (term_row >= VGA_ROWS) {
        term_col = 0;
        term_row = 0;
    }
}

// Print an entire string onto the screen
void term_print(const char* str)
{
    // Keep placing characters until it hits the null-terminating character ('\0)
    for (size_t i = 0; str[i] != '\0'; i++) {
        term_putc(str[i]);
    }
}
