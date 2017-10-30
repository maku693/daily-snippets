#include <algorithm>
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "usage: cat file\n";
    return 1;
  }
  std::string path = argv[1];
  std::ifstream file{path, std::ifstream::in|std::ifstream::binary};
  std::copy(
      std::istream_iterator<char>{file},
      std::istream_iterator<char>{},
      std::ostream_iterator<char>{std::cout});
  return 0;
}
