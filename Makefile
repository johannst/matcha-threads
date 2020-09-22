# Copyright (c) 2020 Johannes Stoelp

AS       := gcc
ASFLAGS  := -g -O0
CXX      := g++
CXXFLAGS := -g -O0 -Wall -Wextra -I.
AR       := ar

lib/libmatcha.a: lib/compile_guard.o lib/thread.o lib/executor.o lib/arch/x86_64/thread_create.o lib/arch/x86_64/yield.o \
                 lib/thread.h lib/executor.h lib/arch/x86_64/asm.h
	$(AR) rcs $@ $(filter %.o,$^)

%.o: %.cc
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

%.o: %.s
	$(AS) -c -o $@ $^ $(ASFLAGS)

fmt:
	fd --type f '.+.h$$|.+.cc$$' --exec clang-format -i {}

example/demo1: example/demo1.o lib/libmatcha.a
	$(CXX) -o $@ $^

gdb: example/demo1
	which cgdb && cgdb -x util.gdb -ex 'start' example/demo1 \
	           ||  gdb -x util.gdb -ex 'start' example/demo1

clean:
	rm -f example/demo1
	rm -f **/*.o **/lib*.a
