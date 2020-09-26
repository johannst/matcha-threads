/* Copyright (c) 2020 Johannes Stoelp */

#include "thread.h"

#include "arch/x86_64/asm.h"
#include "executor.h"

#include <cassert>
#include <cstdint>  // uintN_t
#include <exception>
#include <iostream>
#include <sys/mman.h>  // mmap
#include <unistd.h>    // sysconf

namespace {
    static long get_pagesize() { return ::sysconf(_SC_PAGESIZE); }
}  // namespace

namespace nMatcha {
    Thread::Thread() : mStackPtr(nullptr), mFinished(false), mExecutor(nullptr) {
        const long PAGE_SIZE = get_pagesize();
        const long STACK_SIZE = 8 * PAGE_SIZE;

        // Allocate new stack.
        void* stack = ::mmap(nullptr, STACK_SIZE, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1 /* fd */, 0 /* offset */);
        assert(stack != MAP_FAILED);

        // Simple stack overflow detection by removing permissions from last
        // stack page (lowest addr).
        // In theory stack pointer could be decremented by more than one page
        // and the page below last stack page could be used. However we don't
        // take care of that now and risk the memory corruption.
        int ret = ::mprotect(stack, PAGE_SIZE, PROT_NONE);
        assert(ret == 0);

        // Adjust stack pointer, as stack grows downwards.
        mStackPtr = static_cast<uint8_t*>(stack) + STACK_SIZE;
        {
            static_assert(sizeof(uint64_t) == sizeof(std::uintptr_t), "Pointer must be 64bit!");

            // Setup initial stack frame which will be popped when yielding
            // first time into the thread.
            // Basic idea is to yield into Thread::entry() function which will
            // then call the user function.

            uint64_t* stack = static_cast<uint64_t*>(mStackPtr);
            // Arguments for `thread_create`.
            *(--stack) = reinterpret_cast<uint64_t>(this);
            *(--stack) = reinterpret_cast<uint64_t>(Thread::entry);

            // Yield epilogue.
            *(--stack) = reinterpret_cast<uint64_t>(thread_create);  // Return address
            *(--stack) = static_cast<uint64_t>(0);                   // rbp

            // Callee saved registers.
            *(--stack) = static_cast<uint64_t>(0);                                           // rbx
            *(--stack) = reinterpret_cast<uint64_t>(static_cast<uint64_t*>(mStackPtr) - 4);  // rbp
            *(--stack) = static_cast<uint64_t>(0);                                           // r12
            *(--stack) = static_cast<uint64_t>(0);                                           // r13
            *(--stack) = static_cast<uint64_t>(0);                                           // r14
            *(--stack) = static_cast<uint64_t>(0);                                           // r15

            mStackPtr = static_cast<void*>(stack);
        }
    }

    void Thread::entry(void* obj) {
        Thread* t = static_cast<Thread*>(obj);
        try {
            t->threadFn();
        } catch (const std::exception& e) {
            std::cerr << "Thread: caught unhandled std::exception!\n" << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Thread: caught unhandled unknown exception!" << std::endl;
        }
        t->mFinished = true;
        t->yield();
    }

    void Thread::yield() {
        assert(mExecutor);
        ::yield(mExecutor->getStackPtr(), &mStackPtr);
    }
}  // namespace nMatcha
