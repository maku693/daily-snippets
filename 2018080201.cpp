#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

int main() {
  std::filesystem::path p{"a"};
  std::ifstream file{p};
  std::vector<char> data{std::istreambuf_iterator<char>{file},
                         std::istreambuf_iterator<char>{}};
  for (const auto &c : data) {
    std::cout << c;
  }
}
