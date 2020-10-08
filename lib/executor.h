/* Copyright (c) 2020 Johannes Stoelp */

#pragma once

#include "thread.h"

#include <forward_list>
#include <memory>

namespace nMatcha {
    // Cooperative user thread scheduler.
    //
    // The executor is responsible to schedule the next user thread after one
    // thread yielded, as long as there are user threads that didn't finish.
    //
    // When a `Thread` instance is spawned on an `Executor`, its ownership is
    // transfered to the executor.
    //
    struct Executor {
        Executor(const Executor&) = delete;
        Executor& operator=(const Executor&) = delete;
        Executor() = default;

        const void* getStackPtr() const;

        // Spawn an user thread on the executor.
        void spawn(std::unique_ptr<Thread> t);

        // Run the executor until all user threads are finished.
        // This example executor implements round robin scheduling.
        void run();

      private:
        void* mStackPtr;
        std::forward_list<std::unique_ptr<Thread>> mThreads;

        void yield_to(const Thread* t);
    };
}  // namespace nMatcha
