// This file will contain our x86 assembly code that starts our kernel and sets up the x86

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

// Magic constant GRUB uses to detect the kernel location
.set MB_MAGIC, 0x1BADB002

// Tells GRUB to load modules on page boundaries and provide a memory map
.set MB_FLAGS, (1 << 0) | (1 << 1)

// Calculate a checksum that includes previous values
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

/*
Start the section of the executable that will contain the Multiboot header
*/
.section .multiboot

// Align the following data to a multiple of 4 bytes
.align 4

//
