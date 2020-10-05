/* Copyright (c) 2020 Johannes Stoelp */

#pragma once

#include "thread.h"

#include <forward_list>
#include <memory>

namespace nMatcha {
    struct Executor {
        Executor(const Executor&) = delete;
        Executor& operator=(const Executor&) = delete;
        Executor() = default;

        const void* getStackPtr() const {
            return mStackPtr;
        }

        void spawn(std::unique_ptr<Thread> t);
        void run();

      private:
        void* mStackPtr;
        std::forward_list<std::unique_ptr<Thread>> mThreads;

        void yield_to(const Thread* t) const;
    };
}  // namespace nMatcha
