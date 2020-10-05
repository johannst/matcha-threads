/* Copyright (c) 2020 Johannes Stoelp */

#pragma once

#include <functional>
#include <memory>

namespace nMatcha {
    struct Executor;

    struct Thread {
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        Thread();
        virtual ~Thread() {}

        virtual void threadFn() = 0;

        bool isFinished() const {
            return mFinished;
        }

      protected:
        void yield();

      private:
        static void entry(void* obj);
        void* mStackPtr;
        bool mFinished;

        friend struct Executor;
        const Executor* mExecutor;
    };

    struct Yielder {
        virtual void yield() = 0;
    };

    struct FnThread : public Thread, public Yielder {
        using UserFn = std::function<void(Yielder&)>;
        static std::unique_ptr<Thread> make(UserFn f);

      private:
        virtual void threadFn() override;
        virtual void yield() override;

        UserFn mUserFn;

        enum class CreatorToken {};

      public:
        FnThread(CreatorToken, UserFn f) : mUserFn(f) {}
    };
}  // namespace nMatcha
