#include <cstddef> // size_t
#include <cstdint> // int8_t, int32_t, uint8_t
#include <cstring> // memcpy
#include <iostream> // cout, endl

int main() {
  std::int32_t n = 1;
  const bool is_little_endian = *reinterpret_cast<uint8_t *>(&n) == n;
  if (is_little_endian) {
    std::cout << "Little-Endian\n";
  } else {
    std::cout << "Big-Endian\n";
  }

  int8_t thirteen[4] = {0, 0, 0, 42}; // Big-Endian 32-bit Signed Integer

  std::int32_t non_endian_concerned;
  std::uint8_t non_endian_concerned_buf[sizeof(non_endian_concerned)];
  std::int32_t endian_concerned;
  std::uint8_t endian_concerned_buf[sizeof(endian_concerned)];

  for (std::size_t i = 0; i < sizeof(std::int32_t); i++) {
    std::uint8_t current = static_cast<uint8_t>(thirteen[i]);

    non_endian_concerned_buf[i] = current;

    if (is_little_endian) {
      endian_concerned_buf[sizeof(endian_concerned_buf) - 1 - i] = current;
    } else {
      endian_concerned_buf[i] = current;
    }
  }

  std::memcpy(&endian_concerned, endian_concerned_buf, sizeof(endian_concerned));
  std::memcpy(&non_endian_concerned, non_endian_concerned_buf, sizeof(non_endian_concerned));

  std::cout << endian_concerned << std::endl;
  std::cout << non_endian_concerned << std::endl;
}
