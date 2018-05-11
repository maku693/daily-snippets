#include <cstddef>
#include <cmath>

template <class Vec>
struct VecOperators {
    constexpr Vec& operator-=(const Vec& rhs) noexcept
    {
        return (*this += -rhs);
    }

    constexpr Vec& operator+(const Vec& rhs) noexcept
    {
        return Vec(*this) += rhs;
    }

    constexpr Vec& operator-(const Vec& rhs) noexcept
    {
        return Vec(*this) -= rhs;
    }

    constexpr Vec& operator*=(const float& rhs) noexcept
    {
        for (int i = 0; i < D; i++) {
            this[i] *= rhs;
        }
        return *this;
    }

    constexpr Vec& operator/=(const float& rhs) noexcept
    {
        for (int i = 0; i < D; i++) {
            this[i] *= rhs;
        }
        return *this;
    }
};

struct Vec2 : public VecOperators<Vec2> {
    float x, y;

    constexpr Vec2() noexcept : x(0.0f), y(0.0f) {}

    constexpr Vec2(float v) noexcept : x(v), y(v) {}

    constexpr Vec2(float x, float y) noexcept : x(x), y(y) {}

    constexpr Vec2& operator+() const noexcept
    {
        return *this;
    }

    constexpr Vec2& operator-() const noexcept
    {
        return { -x, -y };
    }
};
