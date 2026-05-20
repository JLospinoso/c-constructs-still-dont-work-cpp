#include <cstdlib>
#include <iostream>
#include <memory>

int main() {
  constexpr std::size_t count = 4;

#if defined(DEMO_INVALID_VOID_PTR)
  // Invalid C++: std::malloc returns void*, and C++ does not implicitly
  // convert void* to int*.
  int* invalid = std::malloc(count * sizeof(int));
  std::free(invalid);
#endif

  // Valid C++ but not idiomatic: the cast only addresses pointer typing.
  auto* values = static_cast<int*>(std::malloc(count * sizeof(int)));
  if (!values) {
    return 1;
  }

  for (std::size_t i = 0; i < count; ++i) {
    values[i] = static_cast<int>(i);
  }

  std::cout << "values[3] = " << values[3] << '\n';
  std::free(values);

  // More idiomatic C++ when you need a dynamic array.
  auto owned = std::make_unique<int[]>(count);
  owned[3] = 3;
  std::cout << "owned[3] = " << owned[3] << '\n';
}
