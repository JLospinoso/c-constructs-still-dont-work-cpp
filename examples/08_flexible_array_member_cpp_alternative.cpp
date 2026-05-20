#include <cstddef>
#include <cstdint>
#include <iostream>
#include <span>
#include <vector>

struct Packet {
  std::uint32_t length{};
  std::vector<std::byte> payload;
};

struct PacketView {
  std::uint32_t length{};
  std::span<const std::byte> payload;
};

Packet make_packet(std::vector<std::byte> payload) {
  return Packet{.length = static_cast<std::uint32_t>(payload.size()),
                .payload = std::move(payload)};
}

int main() {
  auto packet = make_packet({std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}});
  PacketView view{.length = packet.length, .payload = packet.payload};

  std::cout << view.length << ' ' << static_cast<unsigned>(view.payload[3]) << '\n';
}
