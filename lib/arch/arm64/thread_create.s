# Copyright (c) 2020 Johannes Stoelp

    .arch armv8-a
    .section .text, "ax", @progbits

     # extern "C" void thread_create();
    .global thread_create
    .type   thread_create, @function
thread_create:
    .cfi_startproc
    ldr x0, [sp, 0x8]
    ldr x1, [sp]

    blr x1

    # FIXME: no return from thread after user fn finished.
1:
    b 1b
    .cfi_endproc
    .size thread_create, .-thread_create
