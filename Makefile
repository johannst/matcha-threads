# Copyright (c) 2020 Johannes Stoelp

ARCH ?= x86_64

ifeq ($(ARCH),arm64)
PREFIX := aarch64-linux-gnu-
endif

CXX      := $(PREFIX)g++
CXXFLAGS := -g -O0 -Wall -Wextra -I.

lib/libmatcha.a:
	make -C lib ARCH=$(ARCH)

%.o: %.cc
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

fmt:
	fd --type f '.+\.h$$|.+\.cc$$' --exec clang-format -i {}

example/demo1: example/demo1.o lib/libmatcha.a
	$(CXX) -o $@ $^ $(LDFLAGS)
ifeq ($(ARCH),arm64)
	qemu-aarch64                                      \
	    -L /usr/aarch64-linux-gnu                     \
	    -E LD_LIBRARY_PATH=/usr/aarch64-linux-gnu/lib \
	    example/demo1
else
	example/demo1
endif

gdb: example/demo1
ifeq ($(ARCH),arm64)
	qemu-aarch64                                      \
	    -L /usr/aarch64-linux-gnu                     \
	    -E LD_LIBRARY_PATH=/usr/aarch64-linux-gnu/lib \
	    -g 1234                                       \
	    example/demo1 &
	gdb-multiarch -ex 'target remote :1234' -ex 'b main' -ex 'c' example/demo1
else
	which cgdb && cgdb -x util.gdb -ex 'start' example/demo1 \
	           ||  gdb -x util.gdb -ex 'start' example/demo1
endif

docker: docker/Dockerfile
	cd docker && ./build.sh
	docker run -it --rm -v $(PWD):/develop matcha-box:latest
.PHONY: docker


clean:
	make -C lib clean
	rm -f example/demo1 example/demo1.o
