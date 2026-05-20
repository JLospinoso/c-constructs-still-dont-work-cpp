#include <stdio.h>
#include <stdlib.h>

int main(void) {
  const size_t count = 4;

  /* Valid C: malloc returns void*, and C permits the implicit conversion. */
  int* values = malloc(count * sizeof *values);
  if (!values) {
    return 1;
  }

  for (size_t i = 0; i < count; ++i) {
    values[i] = (int)i;
  }

  printf("values[3] = %d\n", values[3]);
  free(values);
  return 0;
}
