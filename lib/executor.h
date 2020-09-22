/* Copyright (c) 2020 Johannes Stoelp */

#pragma once

#include "thread.h"

#include <memory>
#include <vector>

namespace nMatcha {
    struct Executor {
        Executor(const Executor&) = delete;
        Executor& operator=(const Executor&) = delete;
        Executor() = default;

        const void* getStackPtr() const { return mStackPtr; }

        void spawn(std::unique_ptr<Thread> t);
        void run();

      private:
        void* mStackPtr;
        std::vector<std::unique_ptr<Thread>> mThreads;

        void yield_to(const Thread* t) const;
    };
}  // namespace nMatcha
