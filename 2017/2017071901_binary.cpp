#include <fstream>
#include <vector>

std::vector<char> readBinary(const std::string& fileName)
{
    std::ifstream file(fileName, std::ios_base::binary);

    if (file.fail()) {
        throw std::runtime_error("Can't open file");
    }

    return std::vector<char>{ std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>() };
}

int main() { const auto data = readBinary("assets/shader/frag.spv"); }
