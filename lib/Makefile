# Copyright (c) 2020 Johannes Stoelp

AS       := gcc
ASFLAGS  := -g -O0
CXX      := g++
CXXFLAGS := -g -O0 -Wall -Wextra -I.
AR       := ar

ARCH := x86_64

libmatcha.a: compile_guard.o thread.o executor.o               \
             thread.h executor.h                               \
             arch/$(ARCH)/thread_create.o arch/$(ARCH)/yield.o \
             arch/$(ARCH)/init_stack.o                         \
             arch/$(ARCH)/api.h
	$(AR) rcs $@ $(filter %.o,$^)

%.o: %.cc
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

%.o: %.s
	$(AS) -c -o $@ $^ $(ASFLAGS)

clean:
	rm -f *.o **/*.o libmatcha.a
