#include "lib/matcha.h"

#include <cassert>
#include <cstdio>

struct Thread1 : public Thread {
    virtual void threadFn() override {
        puts("start threadFn -> yield()");
        yield();
        puts("return from yield() -> finish threadFn");
    }
} gThread1;

int main() {
    puts("start main thread");

    gThread1.yield_to();

    puts("finish main thread");
    return 0;
}
