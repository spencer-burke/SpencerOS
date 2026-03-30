.global gdt_load
gdt_load:
    # Grab the gdt_ptr argument
    mov 4(%esp), %eax       
    # Load into GDTR
    lgdt (%eax)

    # Kernel data selector
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    # Kernel code selector, reload CS
    ljmp $0x08, $.flush
.flush:
    ret