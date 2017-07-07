#include <cstddef>

struct mat4 {
    float values[16];

    explicit constexpr mat4(float v)
    {
        values = {
            v, 0, 0, 0,
            0, v, 0, 0,
            0, 0, v, 0,
            0, 0, 0, v
        };
    }

    static constexpr vec4 operator[](std::ptrdiff_t i)
    {
        return {
            values[i * 4],
            values[i * 4 + 1],
            values[i * 4 + 2],
            values[i * 4 + 3]
        };
    }

    static constexpr mat4 identity()
    {
        return {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    }

    static constexpr mat4 zero()
    {
        return {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
        };
    }
};
