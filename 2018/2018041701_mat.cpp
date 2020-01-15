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
};

template <class T>
constexpr bool is_square_v = T::rows == T::cols;

template <class T, std::size_t Rows, std::size_t Cols>
constexpr auto identity()
{
    using result_t = mat<T, Rows, Cols>;
    static_assert(is_square_v<result_t>,
        "identity matrix is defined only for square matrix");

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

// TODO: constepxr auto inverse()

template <class T, std::size_t Rows, std::size_t Cols>
constexpr auto transpose(const mat<T, Rows, Cols>& src)
{
    using result_t = mat<T, Cols, Rows>;

    result_t m{};

    for (std::size_t r = 0; r < result_t::rows; r++) {
        for (std::size_t c = 0; c < result_t::cols; c++) {
            m(r, c) = src(c, r);
        }
    }

    return m;
}

template <class LValueType, std::size_t LRows, class RValueType, std::size_t RCols, std::size_t N>
constexpr auto operator * (const mat<LValueType, LRows, N>& lhs, const mat<RValueType, N, RCols>& rhs)
{
    using result_t = mat<LValueType, LRows, RCols>;

    result_t m{};

    for (std::size_t r = 0; r < result_t::rows; r++) {
        for (std::size_t c = 0; c < result_t::cols; c++) {
            typename result_t::value_type v{};
            for (std::size_t i = 0; i < N; i++) {
                v += lhs(r, i) * rhs(i, c);
            }
            m(r, c) = v;
        }
    }

    return m;
}

template <class T, std::size_t Rows, std::size_t Cols>
constexpr bool operator==(const mat<T, Rows, Cols>& lhs, const mat<T, Rows, Cols>& rhs)
{
    using operand_t = mat<T, Rows, Cols>;

    for (std::size_t r = 0; r < operand_t::rows; r++) {
        for (std::size_t c = 0; c < operand_t::cols; c++) {
            if (lhs(r, c) != rhs(r, c)) {
                return false;
            }
        }
    }

    return true;
}

// TODO: constexpr mat<T, 4, 4> persp()
// TODO: constexpr mat<T, 4, 4> ortho()
// TODO: constexpr mat<T, 4, 4> translate(const vec<3>&)
// TODO: constexpr mat<T, 4, 4> rotate(const quaternion&)
// TODO: constexpr mat<T, 4, 4> scale(const vec<3>&)

int main()
{
    using mat1x2 = mat<double, 1, 2>;
    using mat2x1 = mat<double, 2, 1>;
    using mat2x2 = mat<double, 2, 2>;
    using mat3x3 = mat<double, 3, 3>;

    {
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
        constexpr mat2x2 m{{{1, 2}, {3, 4}}};
        static_assert(m(0, 0) == 1);
        static_assert(m(0, 1) == 2);
        static_assert(m(1, 0) == 3);
        static_assert(m(1, 1) == 4);
    }

    {
        static_assert(is_square_v<mat2x2>);
        static_assert(is_square_v<mat3x3>);
        static_assert(!is_square_v<mat1x2>);
        static_assert(!is_square_v<mat2x1>);
    }

    {
        constexpr mat2x2 src{{
            {1, 2},
            {3, 4}
        }};
        constexpr mat2x2 expected {{
            {1, 3},
            {2, 4}
        }};
        constexpr auto actual = transpose(src);
        static_assert(expected == actual);
    }

    {
        constexpr auto m = identity<double, 2, 2>();
        static_assert(m(0, 0) == 1);
        static_assert(m(0, 1) == 0);
        static_assert(m(1, 0) == 0);
        static_assert(m(1, 1) == 1);
    }

    {
        constexpr mat2x1 lhs{{{1.0}, {1.0}}};
        constexpr mat1x2 rhs{{{1.0, 1.0}}};
        constexpr auto m = lhs * rhs;
        // TODO: value test
    }

    {
        constexpr mat1x2 lhs{{{1.0, 1.0}}};
        constexpr mat1x2 rhs{{{1.0, 1.0}}};
        static_assert(lhs == rhs);
    }
}
