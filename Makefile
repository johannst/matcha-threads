CXX := g++
CXXFLAGS := -g -O0 -Wall -Wextra -I.

example/test: example/test.cc lib/thread_create.s lib/matcha.h
	$(CXX) -o $@ $^ $(CXXFLAGS)

fmt:
	fd --type f '.+.h$$|.+.cc$$' --exec clang-format -i {}

gdb: example/test
	which cgdb && cgdb -x util.gdb -ex 'start' example/test \
	           ||  gdb -x util.gdb -ex 'start' example/test

clean:
	rm -f example/test
