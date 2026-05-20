#include <stdio.h>
#include <stdlib.h>

struct Packet {
  unsigned length;
  unsigned char payload[];
};

int main(void) {
  const unsigned length = 4;
  struct Packet* packet = malloc(sizeof *packet + length * sizeof packet->payload[0]);
  if (!packet) {
    return 1;
  }

  packet->length = length;
  for (unsigned i = 0; i < packet->length; ++i) {
    packet->payload[i] = (unsigned char)(i + 1);
  }

  printf("%u %u\n", packet->length, packet->payload[3]);
  free(packet);
  return 0;
}
