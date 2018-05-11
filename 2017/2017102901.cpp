#include <array>
#include <cstdint>
#include <fstream>

int main() {
  std::ofstream of{"out", std::ofstream::out|std::ofstream::binary|std::ofstream::trunc};
  if (of.fail()) {
    return 1;
  }

  std::array<std::uint8_t, 4> data{1, 2, 3, 4};

  for (std::uint8_t elem : data) {
    of.write(reinterpret_cast<char *>(&elem), sizeof(std::uint8_t));
  }
  return 0;
}

