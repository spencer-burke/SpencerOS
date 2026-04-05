.global idt_load
idt_load:
    # Grab the idt_ptr argument
    mov 4(%esp), %eax
    # Load into IDTR
    lidt (%eax)
    # Read it back immediately to verify
    sidt (%eax)
    # Return
    ret
