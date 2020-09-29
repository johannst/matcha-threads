# Copyright (c) 2020 Johannes Stoelp

CXX      := g++
CXXFLAGS := -g -O0 -Wall -Wextra -I.

lib/libmatcha.a:
	make -C lib

%.o: %.cc
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

fmt:
	fd --type f '.+\.h$$|.+\.cc$$' --exec clang-format -i {}

example/demo1: example/demo1.o lib/libmatcha.a
	$(CXX) -o $@ $^

gdb: example/demo1
	which cgdb && cgdb -x util.gdb -ex 'start' example/demo1 \
	           ||  gdb -x util.gdb -ex 'start' example/demo1

clean:
	rm -f example/demo1
	rm -f **/*.o **/lib*.a
