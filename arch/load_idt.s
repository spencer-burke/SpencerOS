.global idt_load
idt_load:
    # Grab the idt_ptr argument
    mov 4(%esp), %eax
    # Load into IDTR
    lidt (%eax)
    # Return
    ret
