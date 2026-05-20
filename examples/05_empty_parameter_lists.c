#include <stdio.h>

void fn() {
  puts("fn called");
}

int main(void) {
#if defined(DEMO_EXTRA_ARGUMENT)
  // In C17 and earlier this may compile because the call is seen without a
  // prototype. That does not make it a defined call to this zero-parameter
  // definition. In C23, a no-parameter declarator behaves as though it used
  // void, so a conforming compiler should diagnose the extra argument.
  fn(42);
#else
  fn();
#endif
  return 0;
}
