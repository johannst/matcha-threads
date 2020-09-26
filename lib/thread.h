/* Copyright (c) 2020 Johannes Stoelp */

#pragma once

namespace nMatcha {
    struct Executor;

    struct Thread {
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        Thread();
        virtual ~Thread() {}

        virtual void threadFn() = 0;

        bool isFinished() const { return mFinished; }

      protected:
        void yield();

      private:
        static void entry(void* obj);
        void* mStackPtr;
        bool mFinished;

        friend struct Executor;
        const Executor* mExecutor;
    };
}  // namespace nMatcha
