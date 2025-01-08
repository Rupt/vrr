CFLAGS_LANGUAGE := -std=gnu99 -fwrapv -fno-strict-aliasing
CFLAGS_STRICT := -pedantic -Werror -Wall -Wextra -Wconversion -Walloca -Wshadow -Wundef -Wwrite-strings
CFLAGS_COMPILE := -Os -march=native
CFLAGS := $(CFLAGS_LANGUAGE) $(CFLAGS_STRICT) $(CFLAGS_COMPILE)

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
