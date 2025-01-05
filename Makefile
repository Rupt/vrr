build/hello.o: source/hello.c source/hello.h build
	clang -c $< -o $@

build:
	mkdir build
