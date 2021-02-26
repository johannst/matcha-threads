# Copyright (c) 2020 Johannes Stoelp

ARCH ?= x86_64

ifeq ($(ARCH),arm64)
PREFIX := aarch64-linux-gnu-
else ifeq ($(ARCH),arm)
PREFIX := arm-linux-gnueabi-
endif

AS       := $(PREFIX)gcc
ASFLAGS  := -g -O0
CXX      := $(PREFIX)g++
CXXFLAGS := -g -O0 -Wall -Wextra -I.
DEPS_GEN := -MMD
AR       := $(PREFIX)ar

OBJS := thread.o executor.o
OBJS += arch/$(ARCH)/thread_create.o arch/$(ARCH)/yield.o arch/$(ARCH)/init_stack.o

DEPS := $(OBJS:%.o=%.d)

libmatcha.a: $(OBJS)
	$(AR) rcs $@ $^

%.o: %.cc
	$(CXX) -c -o $@ $(CXXFLAGS) $(DEPS_GEN) $<

%.o: %.s
	$(AS) -c -o $@ $(ASFLAGS) $< 

clean:
	rm -f $(OBJS) $(DEPS)
	rm -f libmatcha.a

-include $(DEPS)
