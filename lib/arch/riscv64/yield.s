# SPDX-License-Identifier: MIT
#
# Copyright (c) 2021, Johannes Stoelp <dev@memzero.de>

    .macro push reg
        addi sp, sp, -8
        sd \reg, 0(sp)
    .endm

    .macro pop reg
        ld \reg, 0(sp)
        addi sp, sp, 8
    .endm

    .section .text, "ax", @progbits

    # extern "C" void yield(const void* new_stack, void** old_stack);
    #                                   ^^^^^^^^^         ^^^^^^^^^
    #                                   a0 (x10)          a1 (x11)
    .global yield
    .type   yield, @function
yield:
    .cfi_startproc
    # save return address
    push ra

    # push callee saved registers
    push x8
    push x9
    push x18
    push x19
    push x20
    push x21
    push x22
    push x23
    push x24
    push x25
    push x26
    push x27

    # arg0: a0 holds new stack
    # arg1: a1 holds addr to location current stack must be saved
    sd sp, 0(a1)  # save current stack ptr
    mv sp, a0     # switch to new stack ptr

    # pop callee saved registers
    pop x27
    pop x26
    pop x25
    pop x24
    pop x23
    pop x22
    pop x21
    pop x20
    pop x19
    pop x18
    pop x9
    pop x8

    # restore return address
    pop ra

    ret
    .cfi_endproc
    .size yield, .-yield
