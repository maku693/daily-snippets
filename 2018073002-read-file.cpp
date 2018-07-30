#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

int main() {
  const std::filesystem::path path{"./LICENSE"};
  std::ifstream file{path};
  if (file.fail()) {
    throw std::runtime_error("failed to open file");
  }
  std::vector<char> data{std::istreambuf_iterator<char>{file},
                         std::istreambuf_iterator<char>{}};
  for (const auto &c : data) {
    std::cout << c;
  }
}
