#include <stdio.h>

enum Small : unsigned char {
  small_zero = 0,
  small_big = 200,
};

int main(void) {
  enum Small value = small_big;
  printf("%zu %d\n", sizeof value, value);
  return 0;
}
