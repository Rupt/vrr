# vrr

Fast vector operations

## Development dependencies

```console
clang
clang-format
clang-tidy
tcc
```

## Commands

### Compile

```console
make
```

### Run tests

```console
make test
```

Or without building requirements:

```console
run/test
```

### Check sources

```console
make lint
```

Or without building requirements:

```console
run/lint
```

## Style

- Prefer to not nest `#include` directives; document expected inclusions instead.
