#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

struct foo {
  char c;
  float f;
  int32_t i;
};

int main() {
  std::chrono::system_clock::time_point t{};
  const std::filesystem::path path{"./test"};

  foo wfoo{'a', -0.1, 42};
  std::ofstream wfile{path, std::fstream::binary};
  t = std::chrono::system_clock::now();
  wfile.write(reinterpret_cast<char *>(&wfoo), sizeof(wfoo));
  wfile.close();
  std::cout << (std::chrono::system_clock::now() - t).count() << '\n';

  foo rfoo{};
  std::ifstream rfile{path, std::fstream::binary};
  t = std::chrono::system_clock::now();
  rfile.read(reinterpret_cast<char *>(&rfoo), sizeof(rfoo));
  std::cout << (std::chrono::system_clock::now() - t).count() << '\n';
  std::cout << rfoo.c << ',' << rfoo.f << ',' << rfoo.i << '\n';
}
