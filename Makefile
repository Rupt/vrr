.PHONY: default
default: build/hello.o

.PHONY: test
test: default
	./test

.PHONY: lint
lint:
	./lint

build/%.o: source/%.c source/%.h build
	clang -c $< -o $@

build:
	mkdir build

.SUFFIXES:  # disables implicit rules; see https://www.gnu.org/software/make/manual/html_node/Suffix-Rules.html
