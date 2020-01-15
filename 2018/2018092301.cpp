#include <filesystem>
#include <iostream>
#include "png.h"

int main() {
    std::filesystem::path path{"foobar.png"};
    std::ifstream f{path};

    //f.read();
    //bool is_png = png_check_sig()
}
