# matcha-threads

A simple and unsafe implementation of `cooperative-multitasking` in userspace
(see [`fibers`][fiber_wiki]).

This implementation should not be used for anything serious, it was just
created to type some lines of `asm` and filll a few evenings.

Supported platforms are `Linux` running on
- `x86_64`
- `arm64`

### Example

```cpp
// file: demo.cc
#include "lib/executor.h"
#include "lib/thread.h"
#include <cstdio>

struct MyThread : public nMatcha::Thread {
    virtual void threadFn() override {
        puts("like");
        yield();
        puts("tea");
    }
};

int main() {
    nMatcha::Executor e;
    e.spawn(std::make_unique<MyThread>());
    e.spawn(nMatcha::FnThread::make([](nMatcha::Yielder& y) {
        puts("I");
        y.yield();
        puts("green");
    }));
    e.run();
    return 0;
}
```

This example `demo.cc` can be run as
```bash
> make -C lib && g++ -o demo demo.cc -I. lib/libmatcha.a && ./demo
...
I
like
green
tea
```

### Setup development environment
This project provides a [`Dockerfile`](docker/Dockerfile) with all the required
tools pre-installed.

To build and launch a container instance run
```bash
make docker
```
> On the fist invocation this takes some minutes as it needs to build the
> docker image.

Additionally the locally cloned repository will be mounted into the container
instance. This allows to use editors/tools installed on the host and to reduce
the image disk footprint.

### Build and run demo
The `x86_64` demo can be run as
```bash
make demo1
```
The `arm64` demo can be run as
```bash
make ARCH=arm64 demo1
```
> Before starting to compile & run for a different architecture the the current
> build artifacts should be removed via `make clean`.

## License
This project is licensed under the [MIT](LICENSE) license.

[fiber_wiki]: https://en.wikipedia.org/wiki/Fiber_(computer_science)
