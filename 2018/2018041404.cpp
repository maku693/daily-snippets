#include <cstddef>
#include <initializer_list>
#include <type_traits>

template <class T, std::size_t Rows, std::size_t Cols>
class matrix {
public:
    using value_type = T;
    static constexpr std::size_t rows = Rows;
    static constexpr std::size_t cols = Cols;

    constexpr matrix() = default;

    T m[Rows][Cols];

    constexpr const T& operator()(std::size_t row, std::size_t col) const
    {
        return m[row][col];
    }

    constexpr T& operator()(std::size_t row, std::size_t col)
    {
        return m[row][col];
    }

    const T* data() const noexcept { return m; }
    T* data() noexcept { return m; }
};

template <class T, std::size_t Rows, std::size_t Cols>
constexpr auto make_identity()
{
    auto m = matrix<T, Rows, Cols>{};

    for (std::size_t r = 0; r < Rows; r++) {
        for (std::size_t c = 0; c < Cols; c++) {
            if (r == c) {
                m(r, c) = 1;
            }
        }
    }

    return m;
}

template <class L, class R>
constexpr bool is_multipliable_v = L::cols == R::rows;

template <class L, class R>
using multiply_result_t = std::enable_if_t<is_multipliable_v<L, R>, matrix<typename L::value_type, R::rows, L::cols>>;

template <class L, class R>
constexpr auto operator * (const L& lhs, const R& rhs)
{
    using result_t = multiply_result_t<L, R>;
    using value_type = typename result_t::value_type;
    constexpr auto rows = result_t::rows;
    constexpr auto cols = result_t::cols;

    result_t m{};

    for (std::size_t r = 0; r < rows; r++) {
        for (std::size_t c = 0; c < cols; c++) {
            value_type v{};
            for (std::size_t i = 0; i < cols; i++) {
                v += lhs(r, i) * rhs(i, c);
            }
            m(r, c) = v;
        }
    }

    return m;
}

int main()
{
    using mat1x2 = matrix<double, 1, 2>;
    using mat2x1 = matrix<double, 2, 1>;
    using mat2x2 = matrix<double, 2, 2>;
    using mat3x3 = matrix<double, 3, 3>;

    {
        // Default ctor
        constexpr mat3x3 m{};
        static_assert(m(0, 0) == 0);
        static_assert(m(0, 1) == 0);
        static_assert(m(0, 2) == 0);
        static_assert(m(1, 0) == 0);
        static_assert(m(1, 1) == 0);
        static_assert(m(1, 2) == 0);
        static_assert(m(2, 0) == 0);
        static_assert(m(2, 1) == 0);
        static_assert(m(2, 2) == 0);
    }

    {
        // Custom ctor
        constexpr mat2x2 m{{{1.0, 1.0}, {1.0, 1.0}}};
        static_assert(m(0, 0) == 1);
        static_assert(m(0, 1) == 1);
        static_assert(m(1, 0) == 1);
        static_assert(m(1, 1) == 1);
    }

    {
        // Builder
        constexpr auto m = make_identity<double, 2, 2>();
        static_assert(m(0, 0) == 1);
        static_assert(m(0, 1) == 0);
        static_assert(m(1, 0) == 0);
        static_assert(m(1, 1) == 1);
    }

    {
        // Traits
        static_assert(is_multipliable_v<mat2x2, mat2x2>);
        static_assert(is_multipliable_v<mat2x1, mat1x2>);
        static_assert(!is_multipliable_v<mat2x2, mat3x3>);
        static_assert(!is_multipliable_v<mat2x2, mat1x2>);
    }

    {
        // Operators
        // TODO: value test
        constexpr mat2x1 lhs{{{1.0}, {1.0}}};
        constexpr mat1x2 rhs{{{1.0, 1.0}}};
        constexpr auto m = lhs * rhs;
    }
}
