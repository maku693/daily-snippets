#include <array>

struct vec3 {
    int x;
    int y;
    int z;
};

void main()
{
    constexpr int arr[] = { 1, 2, 3 };
    constexpr std::array<int, 3> stdarr = { 1, 2, 3 };
    constexpr vec3 v = { 1, 2, 3 };
}
