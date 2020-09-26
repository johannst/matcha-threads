/* Copyright (c) 2020 Johannes Stoelp */

#include "executor.h"

#include "arch/x86_64/asm.h"

namespace nMatcha {
    void Executor::spawn(std::unique_ptr<Thread> t) {
        mThreads.push_back(std::move(t));
        mThreads.back()->mExecutor = this;
    }

    void Executor::run() {
        for (const std::unique_ptr<Thread>& t : mThreads) {
            if (t->isFinished()) {
                continue;
            }
            yield_to(t.get());
        }
    }

    void Executor::yield_to(const Thread* t) const { ::yield(t->mStackPtr, &mStackPtr); }
}  // namespace nMatcha
