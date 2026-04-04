# This file will contain our x86 assembly code that starts our kernel and sets up the x86

/*
Declare kernel_main label as being external to this file
It's the name of the main C function in 'kernel.c'
*/
.extern kernel_main

/*
We declare 'start' label as global (accessible from outside this file), the linker will need to know where it is
GRUB, the bootloader, will need to know info about the kernel
Valid 'Multiboot header' that is recognized by GRUB needs some constants
We can hardcode those
*/
.global start

# Magic constant GRUB uses to detect the kernel location
.set MB_MAGIC, 0x1BADB002

# Tells GRUB to load modules on page boundaries and provide a memory map
.set MB_FLAGS, (1 << 0) | (1 << 1)

# Calculate a checksum that includes previous values
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

/*
Start the section of the executable that will contain the Multiboot header
*/
.section .multiboot

# Align the following data to a multiple of 4 bytes
.align 4

# Use the previously calculated constants in executable code
.long MB_MAGIC
.long MB_FLAGS
.long MB_CHECKSUM

/*
The section contains data initialized to zeroes when the kernel is loaded
*/
.section .bss

# C code needs a stack, so allocated 4096 bytes(4 kilobytes) for the the stack
# This can be expanded for a larger stack
.align 16
stack_bottom:
    .skip 4096
stack_top:

# This section contains the assembly code to be run when the kernel loads
.section .text

# Create the 'start' label for the first code being run by the kernel
start:

# Set up the stack by setting the stack pointer to the top of the stack
# Stack grows downward, so set it to the top to give it room
mov $stack_top, %esp

# Call the main C function
call kernel_main

# Hang the cpu when the C code runs
    hang:
        # Disable CPU interrupts
        cli
        # Halt the CPU
        hlt
        # Loop and try again
        jmp hang
