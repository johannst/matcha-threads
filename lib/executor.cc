/* Copyright (c) 2020 Johannes Stoelp */

#include "executor.h"

#include "arch.h"

namespace nMatcha {
    const void* Executor::getStackPtr() const {
        return mStackPtr;
    }

    void Executor::spawn(std::unique_ptr<Thread> t) {
        mThreads.push_front(std::move(t));
        mThreads.front()->mExecutor = this;
    }

    void Executor::run() {
        // Round robin until all threads finished.
        while (!mThreads.empty()) {
            for (const std::unique_ptr<Thread>& t : mThreads) {
                if (!t->isFinished()) {
                    yield_to(t.get());
                }
            }
            mThreads.remove_if([](const std::unique_ptr<Thread>& t) { return t->isFinished(); });
        }
    }

    void Executor::yield_to(const Thread* t) {
        ::yield(t->mStack.mPtr, &mStackPtr);
    }
}  // namespace nMatcha
