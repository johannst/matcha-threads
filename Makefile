# Copyright (c) 2020 Johannes Stoelp

AS       := gcc
ASFLAGS  := -g -O0
CXX      := g++
CXXFLAGS := -g -O0 -Wall -Wextra -I.
AR       := ar

lib/libmatcha.a: lib/matcha.o lib/thread_create.o lib/matcha.h
	$(AR) rcs $@ $(filter %.o,$^)

%.o: %.cc
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

%.o: %.s
	$(AS) -c -o $@ $^ $(ASFLAGS)

fmt:
	fd --type f '.+.h$$|.+.cc$$' --exec clang-format -i {}

example/test: example/test.o lib/libmatcha.a
	$(CXX) -o $@ $^

gdb: example/test
	which cgdb && cgdb -x util.gdb -ex 'start' example/test \
	           ||  gdb -x util.gdb -ex 'start' example/test

clean:
	rm -f example/test
	rm -f **/*.o **/lib*.a
