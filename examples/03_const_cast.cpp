#include <iostream>

void legacy_write(int* value) {
  *value = 101;
}

int main() {
  int mutable_value = 100;
  const int* const_view = &mutable_value;

  // Defined: the original object is not const.
  legacy_write(const_cast<int*>(const_view));
  std::cout << mutable_value << '\n';

#if defined(DEMO_UNDEFINED_MODIFY_CONST)
  const int immutable_value = 100;
  int* dangerous = const_cast<int*>(&immutable_value);

  // Compiles, but executing this write is undefined behavior. const_cast
  // removes a type-system barrier; it does not change the object.
  *dangerous = 101;
  std::cout << immutable_value << '\n';
#endif
}
