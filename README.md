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

## Local style

- Prefer to not nest `#include` directives, because textual inclusion is not a
  module system and its abuse as a module system incurs costs for compilers.
  - Instead, document expected includes under `#ifdef VRR_INCLUDE_GUARD` guards in
    all files that may be included elsewhere.
  - To ensure only one set of `#include` directives in a build, undefine the guard
    with `#undef VRR_INCLUDE_GUARD` before your first set of include directives.
