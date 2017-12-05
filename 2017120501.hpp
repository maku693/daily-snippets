#include <array>
#include <cstddef>

#include <2017120202.hpp>

class mat4 {
public:
    class mat4::row {
    public:
        constexpr row() noexcept = default;

        constexpr row(float v1, float v2, float v3, float v4) noexcept
            : m_values{v1, v2, v3, v4}
        {}

        constexpr const float& operator[](std::ptrdiff_t i) const
        {
            return m_values[i];
        }

        constexpr float& operator[](std::ptrdiff_t i)
        {
            return m_values[i];
        }

        constexpr operator vec4() const noexcept
        {
            return { m_values[0], m_values[1], m_values[2], m_values[3] };
        }

    private:
        std::array<float, 4> m_values{};
    };

    constexpr mat4() noexcept = default;

    explicit constexpr mat4(float x) noexcept
    {}

    constexpr mat4(float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33) noexcept
        : m_rows{
            row{m00, m01, m02, m03},
            row{m10, m11, m12, m13},
            row{m20, m21, m22, m23},
            row{m30, m31, m32, m33},
        }
    {}

    constexpr const row& operator[](std::ptrdiff_t i) const
    {
        return m_rows[i];
    }

    constexpr row& operator[](std::ptrdiff_t i)
    {
        return m_rows[i];
    }

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
        // TODO
        return *this;
    }

    constexpr mat4& operator-=(const mat4& rhs) noexcept
    {
        return *this += -rhs;
    }

    constexpr mat4& operator*=(const float rhs) noexcept
    {
        // TODO
        return *this;
    }

    constexpr mat4& operator*=(const mat4& rhs) noexcept
    {
        // TODO
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

    constexpr mat4 operator*(const mat4& rhs) const noexcept
    {
        return mat4(*this) *= rhs;
    }

private:
    std::array<row, 4> m_rows{};
};

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
