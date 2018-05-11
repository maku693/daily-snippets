#include <array>
#include <cstddef>
#include <type_traits>

template <std::size_t Dim>
struct vec {
    std::array<float, Dim> elements = { 0.f };

    constexpr float& operator[](std::ptrdiff_t i) noexcept
    {
        return this->elements[i];
    }

    constexpr vec<Dim>& operator-() noexcept
    {
        for (int i = 0; i < Dim; i++) {
            this->elements[i] *= -1;
        }
        return *this;
    }

    constexpr vec<Dim>& operator+=(const vec<Dim> rhs) noexcept
    {
        for (int i = 0; i < Dim; i++) {
            this->elements[i] += rhs[i];
        }
        return *this;
    }

    constexpr vec<Dim>& operator-=(const vec<Dim>& rhs) noexcept
    {
        return *this += -rhs;
    }

    template <class T>
    constexpr std::enable_if_t<std::is_scalar<T>::value, vec<Dim>&>
    operator*=(T rhs) noexcept
    {
        for (int i = 0; i < Dim; i++) {
            this->elements[i] *= rhs;
        }
        return *this;
    }

    template <class T>
    constexpr std::enable_if_t<std::is_scalar<T>::value, vec<Dim>&>
    operator/=(T rhs) noexcept
    {
        return *this *= (1 / rhs);
    }

    constexpr vec<Dim> operator+(const vec<Dim>& rhs) noexcept
    {
        return vec<Dim>(*this) += rhs;
    }

    constexpr vec<Dim> operator-(const vec<Dim>& rhs) noexcept
    {
        return vec<Dim>(*this) -= rhs;
    }

    constexpr vec<Dim> operator*(const vec<Dim>& rhs) noexcept
    {
        return vec<Dim>(*this) *= rhs;
    }

    constexpr vec<Dim> operator/(const vec<Dim>& rhs) noexcept
    {
        return vec<Dim>(*this) /= rhs;
    }
};

template <std::size_t Dim>
inline constexpr std::enable_if_t<(Dim > 0), float&>
x(const vec<Dim>& v) noexcept { return v[0]; }

template <std::size_t Dim>
inline constexpr std::enable_if_t<(Dim > 1), float&>
y(const vec<Dim>& v) noexcept { return v[1]; }

template <std::size_t Dim>
inline constexpr std::enable_if_t<(Dim > 2), float&>
z(const vec<Dim>& v) noexcept { return v[2]; }

template <std::size_t Dim>
inline constexpr std::enable_if_t<(Dim > 3), float&>
w(const vec<Dim>& v) noexcept { return v[3]; }

// Generate accessor with combination of x, y, z, w

// template <std::size_t Dim>
// inline constexpr float dot(const vec<Dim>& lhs, const vec<Dim>& rhs)
// {
// }

// cross
// mag
// sqrt_mag
// normalize

using vec2 = vec<2>;
using vec3 = vec<3>;

int main()
{
    vec2 v1 = { 1, 2 };
}
