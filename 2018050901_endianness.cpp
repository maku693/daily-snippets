#include <iostream>

int main() {
    int n = 1;
    const bool is_little_endian = *reinterpret_cast<char*>(&n) == 1;
    if (is_little_endian) {
        std::cout << "Little Endian\n";
    } else {
        std::cout << "Big Endian\n";
    }
}
