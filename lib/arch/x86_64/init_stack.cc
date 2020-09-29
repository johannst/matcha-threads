#include <cassert>
#include <cstdint>  // uintN_t

extern "C" void thread_create();

void* init_stack(void* stack_ptr, void (*entry)(void*), void* ctx) {
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
    *(--stack) = reinterpret_cast<uint64_t>(thread_create);  // Return address
    *(--stack) = static_cast<uint64_t>(0);                   // rbp

    // Callee saved registers.
    *(--stack) = static_cast<uint64_t>(0);                                           // rbx
    *(--stack) = reinterpret_cast<uint64_t>(static_cast<uint64_t*>(stack_ptr) - 4);  // rbp
    *(--stack) = static_cast<uint64_t>(0);                                           // r12
    *(--stack) = static_cast<uint64_t>(0);                                           // r13
    *(--stack) = static_cast<uint64_t>(0);                                           // r14
    *(--stack) = static_cast<uint64_t>(0);                                           // r15

    assert((reinterpret_cast<std::uintptr_t>(stack) & 0xf) == 0);  // 16byte aligned
    return static_cast<void*>(stack);
}
