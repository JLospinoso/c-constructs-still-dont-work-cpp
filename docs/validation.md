# Validation notes

Validated locally on 2026-05-20.

```text
gcc --version: Apple clang version 21.0.0 (clang-2100.1.1.101)
clang --version: Apple clang version 21.0.0 (clang-2100.1.1.101)
cmake --version: cmake version 4.3.2

make check: passed
CC=clang CXX=clang++ ./scripts/check.sh: passed
cmake -S . -B build/cmake && cmake --build build/cmake: passed
```

The local `gcc` driver is Apple Clang on this machine. GitHub Actions is the
cross-toolchain check and runs `make check` under GCC and Clang on Ubuntu.

The expected-failure cases are compiler diagnostics, not runtime tests. They
use `-pedantic-errors` and `-Werror` so non-standard C++ extensions, including
Clang's historically permissive out-of-order designated initializer diagnostic,
fail the validation harness.

The C17 empty-parameter-list example is a compile-time demonstration of old
no-prototype behavior. A successful C17-mode compile is not evidence that the
extra-argument call has defined behavior.

The C23 fixed-underlying-enum example is optional in the local script because
C23 implementation support is still uneven. It built and ran locally, printing
`1 200`.
