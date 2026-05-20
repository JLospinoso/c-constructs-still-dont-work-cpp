#include <cassert>
#include <cstddef>
#include <iostream>
#include <span>

void saxpy(std::span<const float> x, std::span<float> y, float a) {
  assert(x.size() == y.size());
  for (std::size_t i = 0; i < x.size(); ++i) {
    y[i] = a * x[i] + y[i];
  }
}

#if defined(__GNUC__) || defined(__clang__)
void saxpy_restrict(std::size_t n,
                    float a,
                    const float* __restrict__ x,
                    float* __restrict__ y) {
  for (std::size_t i = 0; i < n; ++i) {
    y[i] = a * x[i] + y[i];
  }
}
#endif

int main() {
  float x[] = {1.0f, 2.0f, 3.0f};
  float y[] = {10.0f, 20.0f, 30.0f};

  saxpy(x, y, 2.0f);
  std::cout << y[0] << ' ' << y[1] << ' ' << y[2] << '\n';

#if defined(__GNUC__) || defined(__clang__)
  saxpy_restrict(3, 1.0f, x, y);
#endif
}
