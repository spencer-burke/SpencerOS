.global keyboard_isr

keyboard_isr:
    pusha # save all the general purpose registers
    call keyboard_handler # call the c handler
    popa # restore all general purpose registers
    iret # return from the interrupt
