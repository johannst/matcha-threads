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

demo1: example/demo1
ifeq ($(ARCH),arm64)
	qemu-aarch64                                      \
	    -L /usr/aarch64-linux-gnu                     \
	    -E LD_LIBRARY_PATH=/usr/aarch64-linux-gnu/lib \
	    $<
else
	$<
endif

demo1-gdb: example/demo1
ifeq ($(ARCH),arm64)
	qemu-aarch64                                      \
	    -L /usr/aarch64-linux-gnu                     \
	    -E LD_LIBRARY_PATH=/usr/aarch64-linux-gnu/lib \
	    -g 1234                                       \
	    $< &
	gdb-multiarch -ex 'target remote :1234' -ex 'b main' -ex 'c' $<
else
	which cgdb && cgdb --ex 'start' $< \
	           ||  gdb --ex 'start' $<
endif

docker: docker/Dockerfile
	$(eval IMG := matcha-box)
	cd docker && ./build.sh $(IMG)
	docker run -it --rm -v $(PWD):/develop $(IMG):latest
.PHONY: docker

clean:
	make -C lib clean
	rm -f example/demo1 example/demo1.o
