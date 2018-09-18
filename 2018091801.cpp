#include <vector>

struct device {};

struct shader {
    std::vector<char> bytes;
};

struct pipeline {
    shader shader;
};
