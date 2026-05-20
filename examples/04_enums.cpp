#include <iostream>
#include <type_traits>

enum Mode {
  mode_off = 0,
  mode_on = 1,
};

enum class ScopedMode : unsigned {
  off = 0,
  on = 1,
};

int main() {
  int as_int = mode_on; // OK: unscoped enum to int.

#if defined(DEMO_INVALID_INT_TO_ENUM)
  Mode invalid = 1; // Invalid C++: int to enum is not implicit.
  (void)invalid;
#endif

#if defined(DEMO_INVALID_SCOPED_TO_INT)
  int scoped_as_int = ScopedMode::on; // Invalid C++: no implicit enum class to int.
  (void)scoped_as_int;
#endif

  Mode mode = static_cast<Mode>(1);
  auto scoped = static_cast<std::underlying_type_t<ScopedMode>>(ScopedMode::on);

  std::cout << as_int << ' ' << mode << ' ' << scoped << '\n';
}
