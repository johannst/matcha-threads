/* Copyright (c) 2020 Johannes Stoelp */

#include "thread.h"

#include "arch/x86_64/api.h"
#include "executor.h"

#include <cassert>
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

        // Arch specific stack initialization.
        mStackPtr = init_stack(mStackPtr, Thread::entry, static_cast<void*>(this));
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
