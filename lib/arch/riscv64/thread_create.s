# SPDX-License-Identifier: MIT
#
# Copyright (c) 2021, Johannes Stoelp <dev@memzero.de>

    .section .text, "ax", @progbits

     # extern "C" void thread_create();
    .global thread_create
    .type   thread_create, @function
thread_create:
    .cfi_startproc
    ld a0, 8(sp)
    ld t0, 0(sp)

    jalr t0

    # FIXME: no return from thread after user fn finished.
1:
    j 1b
    .cfi_endproc
    .size thread_create, .-thread_create
