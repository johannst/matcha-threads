#include "lib/matcha.h"

#include <cstdio>
#include <memory>

struct TestThread : public Thread {
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

    Executor e;
    e.spawn(std::make_unique<TestThread>("Thread1"));
    e.spawn(std::make_unique<TestThread>("Thread2"));
    e.spawn(std::make_unique<TestThread>("Thread3"));
    e.run();

    puts("[main] finish main thread");
    return 0;
}
