#include <fstream>
#include <iostream>

int main()
{
    std::ifstream f(".clang-format", std::ios::ate);

    if (!f.is_open()) {
        throw std::runtime_error("Can't open the file");
    }

    std::cout << f;
}
