#include <stdio.h>

enum Mode {
  mode_off = 0,
  mode_on = 1,
};

int main(void) {
  int as_int = mode_on;          /* Valid C. */
  enum Mode mode = 1;            /* Valid C; surprising in C++ terms. */
  enum Mode odd_mode = 42;       /* Also valid C; may not be a useful value. */

  printf("%d %d %d\n", as_int, mode, odd_mode);
  return 0;
}
