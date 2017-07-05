#include <array>
#include <cstddef>
#include <cstdint>

inline std::array<std::uint8_t, 4> toLE(std::uint32_t val)
{
    return std::array<std::uint8_t, 4> {
        static_cast<std::uint8_t>(val >> 0),
        static_cast<std::uint8_t>(val >> 8),
        static_cast<std::uint8_t>(val >> 16),
        static_cast<std::uint8_t>(val >> 24)
    };
}

inline std::uint32_t fromLE(std::array<std::uint8_t, 4> data)
{
    return static_cast<std::uint32_t>(data.at(0) << 0) |
        static_cast<std::uint32_t>(data.at(1) << 8) |
        static_cast<std::uint32_t>(data.at(2) << 16) |
        static_cast<std::uint32_t>(data.at(3) << 24);
}

template <std::size_t HeaderSize, std::size_t ContentsSize>
struct Library {
    std::array<std::uint32_t, HeaderSize> offsets;
    std::array<char, ContentSize> contents;

    template <class T>
    T getContentAtIndex(std::uint32_t i)
    {
        return contents.at(i);
    }
};

struct Loader {
};

int main()
{

}
