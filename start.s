.section ".text.boot"

.global _start

_start:
// Halts the core if it's not core 0
    MRS X1, MPIDR_EL1
    AND X1, X1, #3
    CBZ X1, _set_stack_ptr

_halt:  
    WFE
    B _halt

// Set the stack to start in front of the init code  
_set_stack_ptr:
    LDR X1, =_start
    MOV SP, X1

    LDR X1, =__bss_start
    LDR W2, =__bss_size

// Clear the entire BSS segment
_bss_clear_loop:
    CBZ W2, _bss_clear_loop_done
    STR XZR, [X1], #8
    SUB W2, W2, #1
    CBNZ W2, _bss_clear_loop

// Clear done. Jump into main
_bss_clear_loop_done:
    BL kernel_main

// Should never be reached. Halts the core if reached anyways
    B _halt
