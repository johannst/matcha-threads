// SPDX-License-Identifier: MIT
//
// Copyright (c) 2021, Johannes Stoelp <dev@memzero.de>

#include <cassert>
#include <cstdint>  // uintN_t

#if !defined(__APCS_32__)
static_assert(false, "Must be compiled with the Arm Procedure Call Standard (aapcs32)!");
#endif

extern "C" void thread_create();

void* init_stack(void* stack_ptr, void (*entry)(void*), const void* ctx) {
    static_assert(sizeof(uint32_t) == sizeof(std::uintptr_t), "Pointer must be 32bit!");

    // Setup initial stack frame which will be popped when yielding
    // first time into the thread.
    // Basic idea is to yield into Thread::entry() function which will
    // then call the user function.

    uint32_t* stack = static_cast<uint32_t*>(stack_ptr);
    // Arguments for `thread_create`.
    *(--stack) = reinterpret_cast<uint32_t>(ctx);
    *(--stack) = reinterpret_cast<uint32_t>(entry);

    // Yield epilogue.
    *(--stack) = reinterpret_cast<uint32_t>(thread_create);  // r15 (PC)
    *(--stack) = static_cast<uint32_t>(0);                   // r11 (FP)

    // Callee saved registers.
    *(--stack) = static_cast<uint32_t>(0);  // r11
    *(--stack) = static_cast<uint32_t>(0);  // r10
    *(--stack) = static_cast<uint32_t>(0);  // r9
    *(--stack) = static_cast<uint32_t>(0);  // r8
    *(--stack) = static_cast<uint32_t>(0);  // r7
    *(--stack) = static_cast<uint32_t>(0);  // r6
    *(--stack) = static_cast<uint32_t>(0);  // r5
    *(--stack) = static_cast<uint32_t>(0);  // r4

    assert((reinterpret_cast<std::uintptr_t>(stack) & 0x7) == 0);  // 8byte aligned
    return static_cast<void*>(stack);
}
