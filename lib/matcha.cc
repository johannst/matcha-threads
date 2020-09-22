/* Copyright (c) 2020 Johannes Stoelp */

#include "matcha.h"

#include <cassert>
#include <cstdint>
#include <sys/mman.h>
#include <unistd.h>  // sysconf

// asm fns
extern "C" void thread_create();
extern "C" void yield(const void* new_stack, void* const* old_stack);

long get_pagesize() {
    return sysconf(_SC_PAGESIZE);
}

Thread::Thread() {
    const long PAGE_SIZE = get_pagesize();
    const long STACK_SIZE = 8 * PAGE_SIZE;

    // create new stack
    void* stack = mmap(nullptr, STACK_SIZE, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1 /* fd */, 0 /* offset */);
    assert(stack != MAP_FAILED);

    // protect last stack page (lowest addr)
    int ret = mprotect(stack, PAGE_SIZE, PROT_NONE);
    assert(ret == 0);

    // stack grows downwards
    mStackPtr = static_cast<uint8_t*>(stack) + STACK_SIZE;
    {
        uint64_t* stack = static_cast<uint64_t*>(mStackPtr);
        *(--stack) = (uint64_t)this;
        *(--stack) = (uint64_t)Thread::entry;

        // initial values for yield epilog
        *(--stack) = (uint64_t)thread_create;
        *(--stack) = (uint64_t)0;

        // initial values for callee saved regs
        *(--stack) = (uint64_t)0;                                        // rbx
        *(--stack) = (uint64_t)(static_cast<uint64_t*>(mStackPtr) - 4);  // rbp
        *(--stack) = (uint64_t)0;                                        // r12
        *(--stack) = (uint64_t)0;                                        // r13
        *(--stack) = (uint64_t)0;                                        // r14
        *(--stack) = (uint64_t)0;                                        // r15

        mStackPtr = static_cast<void*>(stack);
    }
}

void Thread::entry(void* obj) {
    Thread* t = static_cast<Thread*>(obj);
    t->threadFn();
}

void Thread::yield() {
    assert(mExecutor);
    ::yield(mExecutor->getStackPtr(), &mStackPtr);
}

void Executor::yield_to(const Thread* t) const {
    ::yield(t->mStackPtr, &mStackPtr);
}
