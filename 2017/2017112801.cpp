#include <cmath>

template <class Vec>
struct VecOperators {
    using VecType = Vec;

    constexpr Vec operator+() const noexcept
    {
        return *this;
    }

    constexpr Vec operator-() const noexcept
    {
        return *this * -1.0f;
    }

    constexpr Vec operator-=(const Vec& rhs) noexcept
    {
        return *this += -rhs;
    }

    constexpr Vec operator/=(float rhs) noexcept
    {
        return *this * (1.0f / rhs);
    }

    constexpr Vec operator+(const Vec& rhs) const noexcept
    {
        return Vec(*this) += rhs;
    }

    constexpr Vec operator-(const Vec& rhs) const noexcept
    {
        return Vec(*this) -= rhs;
    }

    constexpr Vec operator*(float rhs) const noexcept
    {
        return Vec(*this) *= rhs;
    }

    constexpr Vec operator/(float rhs) const noexcept
    {
        return Vec(*this) /= rhs;
    }

    constexpr bool operator!=(const Vec& rhs) const noexcept
    {
        return !(*this == rhs);
    }

    constexpr float squared_length() const noexcept
    {
        return dot(*this, *this);
    }

    float length() const noexcept
    {
        return std::sqrt(squared_length());
    }

    Vec normalized() const noexcept
    {
        return *this / length();
    }
};

template <class T>
constexpr typename T::VecType operator*(float lhs, const typename T::VecType& rhs) noexcept
{
    return rhs * lhs;
}

template <class T>
float distance(const typename T::VecType& lhs, const typename T::VecType& rhs)
{
    return (lhs - rhs).length();
}

// lerp(lhs, rhs, d)

struct Vec2 : public VecOperators<Vec2> {
    float x = 0.0f;
    float y = 0.0f;

    constexpr Vec2() noexcept = default;

    constexpr explicit Vec2(float v) noexcept : x(v), y(v) {}

    constexpr Vec2(float x, float y) noexcept : x(x), y(y) {}

    constexpr Vec2 operator+=(const Vec2& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    constexpr Vec2 operator*=(float rhs) noexcept
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    constexpr bool operator==(const Vec2& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
};

constexpr float dot(const Vec2& lhs, const Vec2& rhs) noexcept
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

struct Vec3 : public VecOperators<Vec3> {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    constexpr Vec3() noexcept = default;

    constexpr explicit Vec3(float v) noexcept : x(v), y(v), z(z) {}

    constexpr Vec3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}

    constexpr Vec3 operator+=(const Vec3& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    constexpr Vec3 operator*=(float rhs) noexcept
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    constexpr bool operator==(const Vec3& rhs)
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
};

constexpr Vec3 cross(const Vec3& lhs, const Vec3& rhs) noexcept
{
    return Vec3{
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    };
}

constexpr float dot(const Vec3& lhs, const Vec3& rhs) noexcept
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

// angle(lhs, rhs), reflect(v, n)

struct Vec4 : public VecOperators<Vec4> {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    constexpr Vec4() noexcept = default;

    constexpr explicit Vec4(float v) noexcept : x(v), y(v), z(z), w(w) {}

    constexpr Vec4(float x, float y, float z) noexcept : x(x), y(y), z(z), w(w) {}

    constexpr Vec4 operator+=(const Vec4& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    constexpr Vec4 operator*=(float rhs) noexcept
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    constexpr bool operator==(const Vec4& rhs)
    {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }
};

constexpr float dot(const Vec4& lhs, const Vec4& rhs) noexcept
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
