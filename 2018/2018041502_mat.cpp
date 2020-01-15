#include <cstddef>

template <class T, std::size_t Rows, std::size_t Cols>
class mat {
public:
    using value_type = T;
    static constexpr std::size_t rows = Rows;
    static constexpr std::size_t cols = Cols;

    constexpr mat() = default;

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

    // TODO: constepxr auto inverse()

    // TODO: constepxr auto transpose()
};

template <class T>
constexpr bool is_square_v = T::rows == T::cols;

template <class T, std::size_t Rows, std::size_t Cols>
constexpr auto identity()
{
    using result_t = mat<T, Rows, Cols>;
    static_assert(is_square_v<result_t>, "identity mat is defined only for square mat");

    result_t m{};

    for (std::size_t r = 0; r < result_t::rows; r++) {
        for (std::size_t c = 0; c < result_t::cols; c++) {
            if (r == c) {
                m(r, c) = 1;
            }
        }
    }

    return m;
}

// TODO: constexpr mat<T, 4, 4> persp()
// TODO: constexpr mat<T, 4, 4> ortho()
// TODO: constexpr mat<T, 4, 4> translate(const vec<3>&)
// TODO: constexpr mat<T, 4, 4> rotate(const quaternion&)
// TODO: constexpr mat<T, 4, 4> scale(const vec<3>&)

template <class L, class R>
constexpr bool is_multipliable_v = L::cols == R::rows;

template <class L, class R>
constexpr auto operator * (const L& lhs, const R& rhs)
{
    static_assert(is_multipliable_v<L, R>, "the number of rows of the right mat should be equal to the number of columns of the left mat");

    using result_t = mat<typename L::value_type, L::rows, R::cols>;

    result_t m{};

    for (std::size_t r = 0; r < result_t::rows; r++) {
        for (std::size_t c = 0; c < result_t::cols; c++) {
            typename result_t::value_type v{};
            for (std::size_t i = 0; i < L::cols; i++) {
                v += lhs(r, i) * rhs(i, c);
            }
            m(r, c) = v;
        }
    }

    return m;
}

int main()
{
    using mat1x2 = mat<double, 1, 2>;
    using mat2x1 = mat<double, 2, 1>;
    using mat2x2 = mat<double, 2, 2>;
    using mat3x3 = mat<double, 3, 3>;

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
        constexpr auto m = identity<double, 2, 2>();
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
