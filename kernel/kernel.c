#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "terminal.h"
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
    #error "This code must compiled with a cross-compiler"
#elif !defined(__i386__)
    #error "This code must be compiled with an x86-elf compiler"
#endif

// Kernel main function
void kernel_main()
{
    // Initialize gdt
    gdt_init();

    // Initialize idt
    idt_init();

    // Initialize pic
    pic_init();

    // Initiate terminal
    term_init();

    // Enable interrupts for keyboard
    sti_enable();

    // Display some messages
    term_print("SpencerOS initialized....\n");
}
