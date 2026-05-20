#include <stdio.h>

void saxpy(size_t n, float a, const float* restrict x, float* restrict y) {
  for (size_t i = 0; i < n; ++i) {
    y[i] = a * x[i] + y[i];
  }
}

int main(void) {
  float x[] = {1.0f, 2.0f, 3.0f};
  float y[] = {10.0f, 20.0f, 30.0f};

  saxpy(3, 2.0f, x, y);
  printf("%.1f %.1f %.1f\n", y[0], y[1], y[2]);
  return 0;
}
