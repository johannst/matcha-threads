# Copyright (c) 2020 Johannes Stoelp

# SysV AMD64 ABI
# int/ptr args : rdi, rsi, rdx, rcx, r8, r9
# int/ptr ret  : rax

    .intel_syntax noprefix
    .section .text, "ax", @progbits


     # extern "C" void thread_create();
    .global thread_create
    .type   thread_create, @function
thread_create:
    .cfi_startproc
    mov rdi, qword ptr [rsp+0x8]
    mov rsi, qword ptr [rsp]

    call rsi

    # FIXME: no return from thread after user fn finished.
1:
    jmp 1b
    .cfi_endproc
    .size thread_create, .-thread_create


    # extern "C" void yield(const void* new_stack, void* const* old_stack);
    #                                   ^^^^^^^^^               ^^^^^^^^^
    #                                   rdi                     rsi
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

