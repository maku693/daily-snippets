#include <array>
#include <cstddef>

std::array<uint8_t, 4> toLE(uint32_t val)
{
    return std::array<uint8_t, 4> {
        static_cast<uint8_t>(val >> 0),
        static_cast<uint8_t>(val >> 8),
        static_cast<uint8_t>(val >> 16),
        static_cast<uint8_t>(val >> 24)
    };
}

uint32_t fromLE(std::array<uint8_t, 4> data)
{
    return static_cast<uint32_t>(data.at(0) << 0) |
        static_cast<uint32_t>(data.at(1) << 8) |
        static_cast<uint32_t>(data.at(2) << 16) |
        static_cast<uint32_t>(data.at(3) << 24);
}

#include <iostream>

int main()
{
    const uint32_t val = 100;
    std::cout << val << '\n'
        << static_cast<int>(toLE(val).at(0)) << ','
        << static_cast<int>(toLE(val).at(1)) << ','
        << static_cast<int>(toLE(val).at(2)) << ','
        << static_cast<int>(toLE(val).at(3)) << '\n'
        << fromLE(toLE(val)) << '\n';

    if (fromLE(toLE(val)) == val) {
        return 0;
    } else {
        return -1;
    }
}
