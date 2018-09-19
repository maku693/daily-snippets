#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

struct foo {
  char c;
  float f;
  int32_t i;
};

int main() {
  const std::filesystem::path path{"./test"};

  foo wfoo{'a', -0.1, 42};
  std::ofstream wfile{path, std::fstream::binary};
  wfile.write(reinterpret_cast<char*>(&wfoo.i), sizeof(wfoo.i));
  wfile.write(reinterpret_cast<char*>(&wfoo.c), sizeof(wfoo.c));
  wfile.write(reinterpret_cast<char*>(&wfoo.f), sizeof(wfoo.f));
  wfile.close();

  foo rfoo{};
  std::ifstream rfile{path, std::fstream::binary};
  rfile.read(reinterpret_cast<char*>(&rfoo.i), sizeof(rfoo.i));
  rfile.read(reinterpret_cast<char*>(&rfoo.c), sizeof(rfoo.c));
  rfile.read(reinterpret_cast<char*>(&rfoo.f), sizeof(rfoo.f));
  std::cout << rfoo.c << ',' << rfoo.f << ',' << rfoo.i << '\n';
}
