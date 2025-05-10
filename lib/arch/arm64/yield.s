# SPDX-License-Identifier: MIT
#
# Copyright (c) 2020, Johannes Stoelp <dev@memzero.de>

    .arch armv8-a
    .section .text, "ax", @progbits

    # extern "C" void yield(const void* new_stack, void** old_stack);
    #                                   ^^^^^^^^^         ^^^^^^^^^
    #                                   x0                x1
    .global yield
    .type   yield, @function
yield:
    .cfi_startproc
    // prologue
    stp x29, x30, [sp, -16]!
    mov x29, sp

    // push callee saved registers
    stp x27, x28, [sp, -16]!
    stp x25, x26, [sp, -16]!
    stp x23, x24, [sp, -16]!
    stp x21, x22, [sp, -16]!
    stp x19, x20, [sp, -16]!

    // arg0: x0 holds new stack
    // arg1: x1 holds addr to location current stack must be saved
    mov x2, sp
    str x2, [x1]  // save current stack ptr
    mov sp, x0    // switch to new stack ptr

    // pop callee saved registers
    ldp x19, x20, [sp], 16
    ldp x21, x22, [sp], 16
    ldp x23, x24, [sp], 16
    ldp x25, x26, [sp], 16
    ldp x27, x28, [sp], 16

    // epilogue
    ldp x29, x30, [sp], 16

    ret
    .cfi_endproc
    .size yield, .-yield
