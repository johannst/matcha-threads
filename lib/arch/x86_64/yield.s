# Copyright (c) 2020 Johannes Stoelp

    .intel_syntax noprefix
    .section .text, "ax", @progbits

    # extern "C" void yield(const void* new_stack, void** old_stack);
    #                                   ^^^^^^^^^         ^^^^^^^^^
    #                                   rdi               rsi
    .global yield
    .type   yield, @function
yield:
    .cfi_startproc
    // prologue
    push rbp
    mov rbp, rsp

    // push callee saved registers
    push rbx
    push rbp
    push r12
    push r13
    push r14
    push r15

    // arg0: rdi holds new stack
    // arg1: rsi holds addr to location current stack must be saved
    mov [rsi], rsp  # save current stack ptr
    mov rsp, rdi    # switch to new stack ptr

    // pop callee saved registers
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx

    // epilogue
    mov rsp, rbp
    pop rbp

    ret
    .cfi_endproc
    .size yield, .-yield
