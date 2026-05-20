#!/usr/bin/env bash
set -euo pipefail

CC=${CC:-gcc}
CXX=${CXX:-g++}
BUILD_DIR=${BUILD_DIR:-.build}

CFLAGS=(-Wall -Wextra -pedantic)
CXXFLAGS=(-Wall -Wextra -pedantic)
INVALID_CXXFLAGS=("${CXXFLAGS[@]}" -pedantic-errors -Werror)

mkdir -p "$BUILD_DIR"

say() {
  printf '\n==> %s\n' "$*"
}

run() {
  printf '+ '
  printf '%q ' "$@"
  printf '\n'
  "$@"
}

expect_fail() {
  local name=$1
  shift
  printf '+ expect fail: %s\n' "$name"
  if "$@" >"$BUILD_DIR/${name}.out" 2>"$BUILD_DIR/${name}.err"; then
    printf 'ERROR: expected failure but command succeeded: %s\n' "$name" >&2
    printf 'stdout:\n' >&2
    cat "$BUILD_DIR/${name}.out" >&2
    printf 'stderr:\n' >&2
    cat "$BUILD_DIR/${name}.err" >&2
    return 1
  fi
}

try_optional() {
  local name=$1
  shift
  printf '+ optional: %s\n' "$name"
  if "$@" >"$BUILD_DIR/${name}.out" 2>"$BUILD_DIR/${name}.err"; then
    return 0
  fi

  printf 'WARNING: optional example did not build: %s\n' "$name" >&2
  printf 'stderr:\n' >&2
  cat "$BUILD_DIR/${name}.err" >&2
  return 1
}

say "C17 examples"
run "$CC" -std=c17 "${CFLAGS[@]}" examples/01_void_pointer_malloc.c -o "$BUILD_DIR/01_void_pointer_malloc_c"
run "$CC" -std=c17 "${CFLAGS[@]}" examples/04_enums.c -o "$BUILD_DIR/04_enums_c"
run "$CC" -std=c17 "${CFLAGS[@]}" examples/05_empty_parameter_lists.c -o "$BUILD_DIR/05_empty_parameter_lists_c"
run "$CC" -std=c17 "${CFLAGS[@]}" examples/06_designated_initializers.c -o "$BUILD_DIR/06_designated_initializers_c"
run "$CC" -std=c17 "${CFLAGS[@]}" examples/07_restrict.c -o "$BUILD_DIR/07_restrict_c"
run "$CC" -std=c17 "${CFLAGS[@]}" examples/08_flexible_array_member.c -o "$BUILD_DIR/08_flexible_array_member_c"

say "C++20 examples"
run "$CXX" -std=c++20 "${CXXFLAGS[@]}" examples/01_void_pointer_malloc.cpp -o "$BUILD_DIR/01_void_pointer_malloc_cpp"
run "$CXX" -std=c++20 "${CXXFLAGS[@]}" examples/02_malloc_object_lifetime.cpp -o "$BUILD_DIR/02_malloc_object_lifetime_cpp"
run "$CXX" -std=c++20 "${CXXFLAGS[@]}" examples/03_const_cast.cpp -o "$BUILD_DIR/03_const_cast_cpp"
run "$CXX" -std=c++20 "${CXXFLAGS[@]}" examples/04_enums.cpp -o "$BUILD_DIR/04_enums_cpp"
run "$CXX" -std=c++20 "${CXXFLAGS[@]}" examples/05_empty_parameter_lists.cpp -o "$BUILD_DIR/05_empty_parameter_lists_cpp"
run "$CXX" -std=c++20 "${CXXFLAGS[@]}" examples/06_designated_initializers.cpp -o "$BUILD_DIR/06_designated_initializers_cpp"
run "$CXX" -std=c++20 "${CXXFLAGS[@]}" examples/07_restrict_cpp_extension.cpp -o "$BUILD_DIR/07_restrict_cpp_extension"
run "$CXX" -std=c++20 "${CXXFLAGS[@]}" examples/08_flexible_array_member_cpp_alternative.cpp -o "$BUILD_DIR/08_flexible_array_member_cpp_alternative"

say "Expected C++ failures"
expect_fail invalid_void_ptr "$CXX" -std=c++20 "${INVALID_CXXFLAGS[@]}" -DDEMO_INVALID_VOID_PTR examples/01_void_pointer_malloc.cpp -o "$BUILD_DIR/invalid_void_ptr"
expect_fail invalid_int_to_enum "$CXX" -std=c++20 "${INVALID_CXXFLAGS[@]}" -DDEMO_INVALID_INT_TO_ENUM examples/04_enums.cpp -o "$BUILD_DIR/invalid_int_to_enum"
expect_fail invalid_scoped_to_int "$CXX" -std=c++20 "${INVALID_CXXFLAGS[@]}" -DDEMO_INVALID_SCOPED_TO_INT examples/04_enums.cpp -o "$BUILD_DIR/invalid_scoped_to_int"
expect_fail invalid_extra_argument_cpp "$CXX" -std=c++20 "${INVALID_CXXFLAGS[@]}" -DDEMO_INVALID_EXTRA_ARGUMENT examples/05_empty_parameter_lists.cpp -o "$BUILD_DIR/invalid_extra_argument_cpp"
expect_fail invalid_out_of_order_designator "$CXX" -std=c++20 "${INVALID_CXXFLAGS[@]}" -DDEMO_INVALID_OUT_OF_ORDER examples/06_designated_initializers.cpp -o "$BUILD_DIR/invalid_out_of_order_designator"
expect_fail invalid_array_designator "$CXX" -std=c++20 "${INVALID_CXXFLAGS[@]}" -DDEMO_INVALID_ARRAY_DESIGNATOR examples/06_designated_initializers.cpp -o "$BUILD_DIR/invalid_array_designator"
expect_fail invalid_nested_designator "$CXX" -std=c++20 "${INVALID_CXXFLAGS[@]}" -DDEMO_INVALID_NESTED_DESIGNATOR examples/06_designated_initializers.cpp -o "$BUILD_DIR/invalid_nested_designator"
expect_fail invalid_mixed_designator "$CXX" -std=c++20 "${INVALID_CXXFLAGS[@]}" -DDEMO_INVALID_MIXED_DESIGNATOR examples/06_designated_initializers.cpp -o "$BUILD_DIR/invalid_mixed_designator"

say "C17 vs C23 empty-parameter-list behavior"
run "$CC" -std=c17 "${CFLAGS[@]}" -DDEMO_EXTRA_ARGUMENT examples/05_empty_parameter_lists.c -o "$BUILD_DIR/c17_extra_arg_may_compile"
if "$CC" -std=c2x "${CFLAGS[@]}" -DDEMO_EXTRA_ARGUMENT examples/05_empty_parameter_lists.c -o "$BUILD_DIR/c2x_extra_arg_rejected" >"$BUILD_DIR/c2x_extra_arg.out" 2>"$BUILD_DIR/c2x_extra_arg.err"; then
  printf 'WARNING: compiler accepted the C2x/C23 extra-argument example. This compiler may not implement the C23 change yet.\n' >&2
else
  printf 'C2x/C23 extra-argument example rejected as expected.\n'
fi

say "Optional C23 examples"
if try_optional c23_fixed_underlying_enum "$CC" -std=c2x "${CFLAGS[@]}" examples/09_c23_fixed_underlying_enum.c -o "$BUILD_DIR/09_c23_fixed_underlying_enum_c"; then
  run "$BUILD_DIR/09_c23_fixed_underlying_enum_c"
else
  printf 'Continuing because C23 fixed underlying enum support is still uneven across compilers.\n' >&2
fi

say "Smoke-run selected binaries"
run "$BUILD_DIR/01_void_pointer_malloc_c"
run "$BUILD_DIR/01_void_pointer_malloc_cpp"
run "$BUILD_DIR/06_designated_initializers_c"
run "$BUILD_DIR/06_designated_initializers_cpp"
run "$BUILD_DIR/08_flexible_array_member_c"
run "$BUILD_DIR/08_flexible_array_member_cpp_alternative"

say "Done"
