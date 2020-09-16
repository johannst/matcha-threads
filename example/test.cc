#include "lib/matcha.h"

#include <cassert>
#include <cstdio>

Thread* gThread1 = nullptr;

void thread1_1() {
    puts("thread1_1");
}

void thread1() {
    puts("start thread1");
    thread1_1();
    puts("finish thread1");

    assert(gThread1 != nullptr);
    yield_from(*gThread1);
}

int main() {
    puts("start main thread");

    Thread t(thread1);
    gThread1 = &t;

    yield_to(t);

    gThread1 = nullptr;

    puts("finish main thread");
    return 0;
}
