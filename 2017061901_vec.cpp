#include <cstddef>
#include <type_traits>

template <std::size_t Dim>
struct vec {
    constexpr static std::size_t dim = Dim;
    float elements[Dim];

    constexpr float& operator[](std::ptrdiff_t i) noexcept
    {
        static_assert(Dim <= dim, "");
        return this->elements[i];
    }

    // constexpr vec<Dim> operator=(vec<Dim>&& rhs) noexcept
    // {
    //     for (int i = 0; i < Dim; i++) {
    //         this[i] = std::move(rhs[i]);
    //     }
    //     return *this;
    // }

    // constexpr vec<Dim> operator=(const vec<Dim>& rhs) noexcept
    // {
    //     *this = std::move(vec<Dim>{rhs});
    //     return *this;
    // }

    constexpr vec<Dim>& operator+=(const vec<Dim> rhs) noexcept
    {
        for (int i = 0; i < Dim; i++) {
            this[i] += rhs[i];
        }
        return *this;
    }

    constexpr vec<Dim>& operator-=(const vec<Dim>& rhs) noexcept
    {
        for (int i = 0; i < Dim; i++) {
            this[i] -= rhs[i];
        }
        return *this;
    }

    constexpr vec<Dim> operator+(const vec<Dim>& rhs) noexcept
    {
        return vec<Dim>(*this) += rhs;
    }

    constexpr vec<Dim> operator+(const vec<Dim>& rhs) noexcept
    {
        return vec<Dim>(*this) -= rhs;
    }
};

using vec2 = typename vec<2>;
using vec3 = typename vec<3>;

template <std::size_t Dim>
inline constexpr std::enable_if_t<Dim > 0, float>
x(const vec<Dim>& v) noexcept { return v[0]; }

template <std::size_t Dim>
inline constexpr std::enable_if_t<Dim > 1, float>
y(const vec<Dim>& v) noexcept { return v[1]; }

template <std::size_t Dim>
inline constexpr std::enable_if_t<Dim > 2, float>
z(const vec<Dim>& v) noexcept { return v[2]; }

template <std::size_t Dim>
inline constexpr std::enable_if_t<Dim > 3, float>
w(const vec<Dim>& v) noexcept { return v[3]; }

// template <std::size_t Dim>
// inline constexpr float dot(const vec<Dim>& lhs, const vec<Dim>& rhs)
// {
// }
