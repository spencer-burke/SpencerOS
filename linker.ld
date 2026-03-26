/*
The bootloader will start execution at the symbol designated as the entry point
In this case, that's 'start' (defined in start.s)
*/
ENTRY(start)

/*
Tell the linker part of the compiler where the various sections of the kernel will be put into the final kernel executable
*/
SECTIONS
{
    /*
    Begin putting sections at 1 Megabyte (1M), a good place for kernels to be loaded at by the bootloader
    This is because memory below 1 M is reserved for other x86-related things
    So it's not usable
    */
    . = 1M;

    /*
    We align all the sections in the executable at multiple of 4 Kilobytes (4K)
    This will be come useful later in development when we add paging
    First put the multiboot header, as it's requierd to be near the start of the executable otherwise the bootloader won't find it
    The Multiboot header is Read-Only data, so we can put it in a '.rodata' section
    */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
    }

    /*
    Executable code
    */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.text)
    }

    /*
    Read-only data
    */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /*
    Read-write data (initialized)
    */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /*
    Read-write data (uninitialized) and stack
    */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
