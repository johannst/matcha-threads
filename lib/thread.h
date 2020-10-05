/* Copyright (c) 2020 Johannes Stoelp */

#pragma once

#include <functional>
#include <memory>

namespace nMatcha {
    struct Executor;

    // An abstract base class for implementing cooperative user threads.
    //
    // # Usage
    //
    // To implement a cooperative user thread following interface invoked by
    // the Executor must be implemented:
    //     virtual void threadFn() = 0;
    // By calling `yield()` a thread can give control back to the executor.
    //
    // # Example
    //
    // ```cpp
    // class MyThread : public nMatcha::Thread {
    //     virtual void threadFn() override {
    //         puts("Hello");
    //         yield();
    //         puts("World");
    //     }
    // };
    // ```
    //
    struct Thread {
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        Thread();
        virtual ~Thread() {}

        bool isFinished() const;

      protected:
        void yield();

      private:
        virtual void threadFn() = 0;

        static void entry(void* ctx);
        void* mStackPtr;
        bool mFinished;

        friend struct Executor;
        const Executor* mExecutor;
    };

    // Helper interface to implement yielding for function objects.
    struct Yielder {
        virtual void yield() = 0;
    };

    // Utility class to create cooperative user threads from function objects.
    //
    // # Example
    //
    // ```cpp
    // auto t = nMatcha::FnThread::make([](nMatcha::Yielder& y) {
    //     puts("Hello");
    //     y.yield();
    //     puts("World");
    // });
    // ```
    //
    struct FnThread : public Thread, public Yielder {
        using UserFn = std::function<void(Yielder&)>;

        // Factory method to create `FnThread` objects.
        static std::unique_ptr<Thread> make(UserFn f);

      private:
        UserFn mUserFn;
        virtual void threadFn() override;
        virtual void yield() override;

        enum class CreatorToken {};

      public:
        FnThread(CreatorToken, UserFn f) : mUserFn(f) {}
    };
}  // namespace nMatcha
