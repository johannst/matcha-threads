# SPDX-License-Identifier: MIT
#
# Copyright (c) 2020, Johannes Stoelp <dev@memzero.de>

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
