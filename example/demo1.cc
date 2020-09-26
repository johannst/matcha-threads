/* Copyright (c) 2020 Johannes Stoelp */

#include "lib/executor.h"
#include "lib/thread.h"

#include <cstdio>
#include <memory>

struct TestThread : public nMatcha::Thread {
    TestThread(const char* name) : Thread(), mName(name) {}

    virtual void threadFn() override {
        printf("[%s] starting up TestThread -> yield()\n", mName);
        yield();
        printf("[%s] yield() -> finishing TestThreads\n", mName);
    }

  private:
    const char* mName;
};

int main() {
    puts("[main] start main thread");

    nMatcha::Executor e;
    e.spawn(std::make_unique<TestThread>("Thread1"));
    e.spawn(std::make_unique<TestThread>("Thread2"));
    e.spawn(std::make_unique<TestThread>("Thread3"));
    e.run();
    e.run();

    puts("[main] finish main thread");
    return 0;
}
