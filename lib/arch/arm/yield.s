# SPDX-License-Identifier: MIT
#
# Copyright (c) 2021, Johannes Stoelp <dev@memzero.de>

    .arch armv7-a
    .section .text, "ax", %progbits

    # extern "C" void yield(const void* new_stack, void** old_stack);
    #                                   ^^^^^^^^^         ^^^^^^^^^
    #                                   x0                x1
    .global yield
    .type   yield, %function
yield:
    .cfi_startproc
    // prologue
    push {fp, lr}
    mov fp, sp

    // push callee saved registers
    push {r4-r11}

    // arg0: r0 holds new stack
    // arg1: r1 holds addr to location current stack must be saved
    mov r2, sp
    str r2, [r1]  // save current stack ptr
    mov sp, r0    // switch to new stack ptr

    // pop callee saved registers
    pop {r4-r11}

    // epilogue
    pop {fp, pc}
    .cfi_endproc
    .size yield, .-yield
