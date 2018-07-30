#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

int main() {
  const std::filesystem::path path{"./README.md"};
  std::basic_ifstream<char> file{path, std::ios::binary};
  if (file.fail()) {
    throw std::runtime_error("failed to open file");
  }
  std::vector<char> data{std::istreambuf_iterator<char>{file},
                              std::istreambuf_iterator<char>{}};
  for (const auto &c : data) {
    std::cout << c << '\n';
  }
}
