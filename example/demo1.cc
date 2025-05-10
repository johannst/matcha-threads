// SPDX-License-Identifier: MIT
//
// Copyright (c) 2020, Johannes Stoelp <dev@memzero.de>

#include "lib/executor.h"
#include "lib/thread.h"

#include <cstdio>
#include <memory>

struct TestThread : public nMatcha::Thread {
    TestThread(const char* name) : Thread(), mName(name) {}

    virtual void threadFn() override {
        printf("[TestThread(%s)] start -> yield\n", mName);
        yield();
        printf("[TestThread(%s)] yield -> done\n", mName);
    }

  private:
    const char* mName;
};

void freeThreadFn(nMatcha::Yielder& y) {
    puts("[freeThreadFn] start -> yield");
    y.yield();
    puts("[freeThreadFn] yield -> done");
}

int main() {
    puts("[main] start main thread");

    nMatcha::Executor e;
    e.spawn(std::make_unique<TestThread>("Thread1"));
    e.spawn(std::make_unique<TestThread>("Thread2"));
    e.spawn(std::make_unique<TestThread>("Thread3"));

    e.spawn(nMatcha::FnThread::make([](nMatcha::Yielder& y) {
        puts("[Lambda Thread] start -> yield");
        y.yield();
        puts("[Lambda Thread] yield -> done");
    }));

    e.spawn(nMatcha::FnThread::make(freeThreadFn));

    e.run();

    puts("[main] finish main thread");
    return 0;
}
