#include <iostream>

struct Options {
  int timeout_ms;
  bool verbose = false;
  int retries = 0;
};

struct Inner {
  int x;
  int y;
};

struct Outer {
  Inner inner;
  int z;
};

int main() {
  // Valid C++20: direct non-static data members, in declaration order.
  Options ok{.timeout_ms = 5000, .verbose = true, .retries = 3};

  // Also valid: omitted members are initialized normally.
  Options defaults{.timeout_ms = 2500, .retries = 1};

#if defined(DEMO_INVALID_OUT_OF_ORDER)
  Options out_of_order{.retries = 3, .timeout_ms = 5000};
  (void)out_of_order;
#endif

#if defined(DEMO_INVALID_ARRAY_DESIGNATOR)
  int table[4] = {[2] = 99};
  (void)table;
#endif

#if defined(DEMO_INVALID_NESTED_DESIGNATOR)
  Outer nested{.inner.x = 7, .z = 9};
  (void)nested;
#endif

#if defined(DEMO_INVALID_MIXED_DESIGNATOR)
  Options mixed{5000, .retries = 3};
  (void)mixed;
#endif

  std::cout << ok.timeout_ms << ' ' << ok.verbose << ' ' << defaults.retries << '\n';
}
