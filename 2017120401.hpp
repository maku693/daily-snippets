struct mat4 {
    constexpr mat4() noexcept = default;

    explicit constexpr mat4(float x) noexcept
    {}

    constexpr mat4(float m01, float m02, float m03, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44) noexcept
    {}

private:
    vec4 value[4] = { {}, {}, {}, {} };

    constexpr mat4 operator+() const noexcept
    {
        return *this;
    }

    constexpr mat4 operator-() const noexcept
    {
        return *this * -1.0f;
    }

    constexpr mat4& operator+=(const mat4& rhs) noexcept
    {
        //
        return *this;
    }

    constexpr mat4& operator-=(const mat4& rhs) noexcept
    {
        return *this += -rhs;
    }

    constexpr mat4& operator*=(const float rhs) noexcept
    {
        //
        return *this;
    }

    constexpr mat4& operator*=(const mat4& rhs) noexcept
    {
        //
        return *this;
    }

    constexpr mat4 operator+(const mat4& rhs) const noexcept
    {
        return mat4(*this) += rhs;
    }

    constexpr mat4 operator-(const mat4& rhs) const noexcept
    {
        return mat4(*this) -= rhs;
    }

    constexpr mat4 operator*(const float rhs) const noexcept
    {
        return mat4(*this) *= rhs;
    }
};

class mat4_row_view;

// constexpr mat4 make_identity_mat4() noexcept
// {
//     return mat4{
//         1.0f, 0.0f, 0.0f, 0.0f,
//         0.0f, 1.0f, 0.0f, 0.0f,
//         0.0f, 0.0f, 1.0f, 0.0f,
//         0.0f, 0.0f, 0.0f, 1.0f
//     };
// }

// constexpr mat4 make_scale(const float x, const float y,
//     const float z) noexcept
// {
//     return mat4{
//         x,    0.0f, 0.0f, 0.0f,
//         0.0f, y,    0.0f, 0.0f,
//         0.0f, 0.0f, z,   0.0f,
//         0.0f, 0.0f, 0.0f, 1.0f
//     };
// }
