#include <stdio.h>

struct Inner {
  int x;
  int y;
};

struct Outer {
  struct Inner inner;
  int z;
};

int main(void) {
  struct Inner out_of_order = {.y = 2, .x = 1};
  int table[4] = {[2] = 99};
  struct Outer nested = {.inner.x = 7, .z = 9};
  struct Inner mixed = {1, .y = 2};

  printf("%d %d %d %d\n", out_of_order.x, table[2], nested.inner.x, mixed.y);
  return 0;
}
