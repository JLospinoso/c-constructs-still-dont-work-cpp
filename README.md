# C Constructs That Still Don’t Work in C++

[![check](https://github.com/JLospinoso/c-constructs-still-dont-work-cpp/actions/workflows/check.yml/badge.svg)](https://github.com/JLospinoso/c-constructs-still-dont-work-cpp/actions/workflows/check.yml)

Companion repo for the 2026 follow-up post:

- Blog post: [C Constructs That Still Don’t Work in C++ — and a Few That Changed](https://lospino.so/blog/c-constructs-that-still-dont-work-in-cpp/) (forthcoming).
- `examples/` — small C and C++ examples backing the claims in the post.
- `scripts/check.sh` — compiles the valid examples and verifies selected invalid examples fail.

The point of the repo is not to prove every corner of the standards. It is to keep the article honest with examples a reader can run.

This repo is not a style guide for writing C++ with C allocation and C layouts.
Several examples are intentionally non-idiomatic because they isolate
language-boundary behavior.

The examples are also available as focused Compiler Explorer links in
[`docs/godbolt-links.md`](docs/godbolt-links.md). Use those when you want to
see diagnostics immediately; use this repository when you want repeatable local
checks.

## Quick start

```sh
make check
```

or directly:

```sh
./scripts/check.sh
```

The script defaults to:

- `gcc` for C examples
- `g++` for C++ examples
- C17 for old C behavior
- C2x/C23 where the empty-parameter-list change matters
- C++20 for designated initializers, `std::span`, and implicit-lifetime examples

Override compilers if needed:

```sh
CC=clang CXX=clang++ ./scripts/check.sh
```

## What the checks do

The script compiles valid examples and also builds a few intentionally-invalid
examples with `DEMO_INVALID_*` macros enabled. Those should fail. If they
compile, either the compiler is accepting an extension or the example needs
adjustment.

Expected-invalid examples use stricter diagnostic flags (`-pedantic-errors` and
`-Werror`) because Clang, GCC, or both may otherwise accept some non-standard
C++ forms as extensions.

The C17 empty-parameter-list example is a compile-time demonstration of old
no-prototype behavior. A successful C17-mode compile is not evidence that the
extra-argument call has defined behavior.

CI runs the same checks with GCC and Clang on Ubuntu.

## Toolchain assumptions

- GCC and Clang are tested.
- C23 support is still uneven; the script uses `-std=c2x` where C23 behavior is
  needed.
- The C23 fixed-underlying-enum example is optional in the script. It runs when
  the selected C compiler supports the syntax and reports a warning otherwise.
- MSVC extension behavior is described from Microsoft documentation in the
  article, but it is not exercised by this CI matrix.

## Test paths

| Test path | Purpose |
|---|---|
| `make check` | Builds valid examples, verifies expected-invalid examples fail, and runs selected binaries. |
| `cmake --build` | Builds valid C17 and C++20 examples only. It does not test expected-failure cases. |
| GitHub Actions | Runs `make check` under GCC and Clang. |

## Repository layout

```text
.
├── CMakeLists.txt
├── Makefile
├── README.md
├── docs/
│   ├── compatibility-matrix.md
│   ├── godbolt-links.md
│   └── validation.md
├── examples/
│   ├── 01_void_pointer_malloc.c
│   ├── 01_void_pointer_malloc.cpp
│   ├── 02_malloc_object_lifetime.cpp
│   ├── 03_const_cast.cpp
│   ├── 04_enums.c
│   ├── 04_enums.cpp
│   ├── 05_empty_parameter_lists.c
│   ├── 05_empty_parameter_lists.cpp
│   ├── 06_designated_initializers.c
│   ├── 06_designated_initializers.cpp
│   ├── 07_restrict.c
│   ├── 07_restrict_cpp_extension.cpp
│   ├── 08_flexible_array_member.c
│   ├── 08_flexible_array_member_cpp_alternative.cpp
│   └── 09_c23_fixed_underlying_enum.c
└── scripts/
    └── check.sh
```

## Suggested publication flow

1. Run `make check` on your target toolchains.
2. Publish the blog post at the linked URL.
3. Link this repo from the post as the runnable companion.

## License

MIT.
