CFLAGS := -Os -std=gnu99 -fwrapv -march=native -pedantic -Wall -Wextra -Werror

.PHONY: test
test: build/hello.o
	run/test

.PHONY: lint
lint:
	run/lint

build/%.o: source/%.c source/%.h build
	clang $(CFLAGS) -DVRR_INCLUDE_GUARD -c $< -o $@

build:
	mkdir build

.SUFFIXES:  # disables implicit rules; see https://www.gnu.org/software/make/manual/html_node/Suffix-Rules.html
