#include <cstddef>

namespace Riff {

template <uint32_t Size>
struct Chunk {
    char fourCC[4];
    uint32_t size = Size;
    char payload[Size];
};

template <uint32_t Size>
struct Riff : Chunk<Size> {
    char fourCC[4] = { 'R', 'I', 'F', 'F' };
};

template <uint32_t Size>
struct List : Chunk<Size> {
    char fourCC[4] = { 'L', 'I', 'S', 'T' };
};

template <class T>
auto toChar(const T& chunk)
{
    // TODO
}

template <size_t Size>
auto makeRiff(const char payload[Size])
{
    Riff<Size> riff;
    riff.payload = payload;
    return riff;
}

template <size_t Size>
auto makeChunk(const char[4] id, const char payload[Size])
{
    Chunk<Size> chunk;
    chunk.id = id;
    chunk.payload = payload;
    return chunk;
}

} // namespace Riff

int main()
{
    const char[] str = "asd";
    const auto chunk = Riff::makeChunk({'T','E','S','T'}, str);
    const auto riff = Riff::makeRiff(Riff::toChar(chunk));
}
