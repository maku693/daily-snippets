#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <type_traits>

struct foo {
  char c;
  float f;
  std::int16_t i;
};

template <class T>
std::enable_if_t<std::is_integral_v<T>, T> swap_to_big(T i) noexcept {
  std::int16_t n = 1;
  const bool is_big = *reinterpret_cast<int8_t *>(&n) != 1;
  if (is_big) {
    return i;
  }
  std::array<char, sizeof(T)> bytes{};
  std::memcpy(bytes.data(), &i, sizeof(T));
  std::swap(bytes.begin(), bytes.end());
  return *reinterpret_cast<T *>(bytes.data());
}

int main() {
  std::chrono::system_clock::time_point t{};
  const std::filesystem::path path{"./test"};

  foo wfoo{'a', -0.1, 42};
  std::ofstream wfile{path, std::fstream::binary};
  wfile.write(reinterpret_cast<char*>(&wfoo.c), sizeof(wfoo.c));
  wfile.write(reinterpret_cast<char*>(&wfoo.f), sizeof(wfoo.f));
  auto wi = swap_to_big(wfoo.i);
  wfile.write(reinterpret_cast<char*>(&wi), sizeof(wi));
  wfile.close();
}
