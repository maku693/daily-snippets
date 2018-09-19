#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

struct foo {
  int32_t i;
  char c;
  float f;
};

int main() {
  const std::filesystem::path path{"./test"};
  foo wfoo{42, 'a', -0.1};
  std::ofstream wfile{path, std::fstream::binary};
  wfile << wfoo.i;
  wfile << wfoo.c;
  wfile << wfoo.f;
  foo rfoo{};
  std::ifstream rfile{path, std::fstream::binary};
  rfile >> rfoo.i;
  rfile >> rfoo.c;
  rfile >> rfoo.f;
  std::cout << rfoo.i << ',' << rfoo.c << ',' << rfoo.f << '\n';
}
