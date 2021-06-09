/* Copyright (c) 2021 Johannes Stoelp */

#include <cassert>
#include <cstdint>  // uintN_t

extern "C" void thread_create();

void* init_stack(void* stack_ptr, void (*entry)(void*), const void* ctx) {
    static_assert(sizeof(uint64_t) == sizeof(std::uintptr_t), "Pointer must be 64bit!");

    // Setup initial stack frame which will be popped when yielding
    // first time into the thread.
    // Basic idea is to yield into Thread::entry() function which will
    // then call the user function.

    uint64_t* stack = static_cast<uint64_t*>(stack_ptr);
    // Arguments for `thread_create`.
    *(--stack) = reinterpret_cast<uint64_t>(ctx);
    *(--stack) = reinterpret_cast<uint64_t>(entry);

    // Yield epilogue.
    *(--stack) = reinterpret_cast<uint64_t>(thread_create);  // Return address (ra)

    // Callee saved registers.
    *(--stack) = static_cast<uint64_t>(0);  // x8
    *(--stack) = static_cast<uint64_t>(0);  // x9
    *(--stack) = static_cast<uint64_t>(0);  // x18
    *(--stack) = static_cast<uint64_t>(0);  // x19
    *(--stack) = static_cast<uint64_t>(0);  // x20
    *(--stack) = static_cast<uint64_t>(0);  // x21
    *(--stack) = static_cast<uint64_t>(0);  // x22
    *(--stack) = static_cast<uint64_t>(0);  // x23
    *(--stack) = static_cast<uint64_t>(0);  // x24
    *(--stack) = static_cast<uint64_t>(0);  // x25
    *(--stack) = static_cast<uint64_t>(0);  // x26
    *(--stack) = static_cast<uint64_t>(0);  // x27

    return static_cast<void*>(stack);
}
