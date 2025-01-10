CFLAGS_LANGUAGE := -std=gnu99 -fwrapv -fno-strict-aliasing
CFLAGS_STRICT := -pedantic -Werror -Wall -Wextra -Wconversion -Walloca -Wshadow -Wundef -Wwrite-strings -Wvla
CFLAGS_COMPILE := -Os -march=native
CFLAGS := $(CFLAGS_LANGUAGE) $(CFLAGS_STRICT) $(CFLAGS_COMPILE)

default: build/chacha.o build/chrono.o

.PHONY: test
test: build/chacha.o
	run/test

.PHONY: lint
lint:
	run/lint

.PHONY: time
time: build/chrono.o
	run/time

build/%.o: source/%.c source/%.h build/.vrr
	clang $(CFLAGS) -DVRR_INCLUDE_GUARD -c $< -o $@

build/.vrr:
	mkdir -p build
	touch $@

.SUFFIXES:  # disables implicit rules; see https://www.gnu.org/software/make/manual/html_node/Suffix-Rules.html
