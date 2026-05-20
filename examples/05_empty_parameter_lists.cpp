#include <iostream>

void fn() {
  std::cout << "fn called\n";
}

int main() {
#if defined(DEMO_INVALID_EXTRA_ARGUMENT)
  fn(42); // Invalid C++: void fn() means no parameters.
#else
  fn();
#endif
}
