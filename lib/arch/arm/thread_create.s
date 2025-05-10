# SPDX-License-Identifier: MIT
#
# Copyright (c) 2021, Johannes Stoelp <dev@memzero.de>

    .arch armv7-a
    .section .text, "ax", %progbits

     # extern "C" void thread_create();
    .global thread_create
    .type   thread_create, %function
thread_create:
    .cfi_startproc
    ldr r0, [sp, #0x4]
    ldr r1, [sp]

    blx r1

    # FIXME: no return from thread after user fn finished.
1:
    b 1b
    .cfi_endproc
    .size thread_create, .-thread_create
