// LDFLAGS="-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib" clang++ --std=c++17 -Wextra -Wextra 2018041801_linmath.cpp
#include <cstddef>

template <class T, std::size_t N>
class vec {
public:
    using value_type = T;

    T v[N];

    constexpr vec() = default;

    constexpr const value_type& operator[](std::size_t i) const { return v[i]; }
    constexpr value_type& operator[](std::size_t i) { return v[i]; }

    constexpr std::size_t size() const noexcept { return N; }

    const T* data() const noexcept { return v; }
    T* data() noexcept { return v; }
};

template <class T, std::size_t Rows, std::size_t Cols>
class mat {
public:
    using value_type = T;
    using row_type = vec<T, Cols>;

    row_type m[Rows];

    constexpr mat() = default;

    constexpr const row_type& operator[](std::size_t i) const { return m[i]; }
    constexpr row_type& operator[](std::size_t i) { return m[i]; }

    constexpr std::size_t rows() const noexcept { return Rows; }
    constexpr std::size_t cols() const noexcept { return Cols; }

    constexpr std::size_t size() const noexcept { return Rows * Cols; }

    const T* data() const noexcept { return m; }
    T* data() noexcept { return m; }
};

template <class T, std::size_t Rows, std::size_t Cols>
constexpr auto identity()
{
    static_assert(Rows == Cols, "identity matrix is defined only for square matrix");

    mat<T, Rows, Cols> m{};

    for (std::size_t r = 0; r < Rows; r++) {
        for (std::size_t c = 0; c < Cols; c++) {
            if (r == c) {
                m[r][c] = 1;
            }
        }
    }

    return m;
}

// TODO: constepxr auto inverse()

template <class T, std::size_t Rows, std::size_t Cols>
constexpr auto transpose(const mat<T, Rows, Cols>& src)
{
    mat<T, Cols, Rows> m{};

    for (std::size_t r = 0; r < Rows; r++) {
        for (std::size_t c = 0; c < Cols; c++) {
            m[r][c] = src[c][r];
        }
    }

    return m;
}

template <class LValueType, std::size_t LRows, class RValueType, std::size_t RCols, std::size_t N>
constexpr auto operator * (const mat<LValueType, LRows, N>& lhs, const mat<RValueType, N, RCols>& rhs)
{
    mat<LValueType, LRows, RCols> m{};

    for (std::size_t r = 0; r < LRows; r++) {
        for (std::size_t c = 0; c < RCols; c++) {
            LValueType v{};
            for (std::size_t i = 0; i < N; i++) {
                v += lhs[r][i] * rhs[i][c];
            }
            m[r][c] = v;
        }
    }

    return m;
}

template <class T, std::size_t Rows, std::size_t Cols>
constexpr bool operator==(const mat<T, Rows, Cols>& lhs, const mat<T, Rows, Cols>& rhs)
{
    for (std::size_t r = 0; r < Rows; r++) {
        for (std::size_t c = 0; c < Cols; c++) {
            if (lhs[r][c] != rhs[r][c]) {
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
    using mat2x2 = mat<double, 2, 2>;

    {
        constexpr mat2x2 m{};
        static_assert(m[0][0] == 0);
        static_assert(m[0][1] == 0);
        static_assert(m[1][0] == 0);
        static_assert(m[1][1] == 0);
    }

    {
        constexpr mat2x2 m{1, 2, 3, 4};
        static_assert(m[0][0] == 1);
        static_assert(m[0][1] == 2);
        static_assert(m[1][0] == 3);
        static_assert(m[1][1] == 4);
    }

    {
        constexpr mat2x2 src{1, 2, 3, 4};
        constexpr mat2x2 expected{1, 3, 2, 4};
        constexpr auto actual = transpose(src);
        static_assert(expected == actual);
    }

    {
        constexpr auto m = identity<double, 2, 2>();
        static_assert(m[0][0] == 1);
        static_assert(m[0][1] == 0);
        static_assert(m[1][0] == 0);
        static_assert(m[1][1] == 1);
    }

    {
        constexpr mat2x2 lhs{1, 1, 1, 1};
        constexpr mat2x2 rhs{1, 1, 1, 1};
        constexpr auto m = lhs * rhs;
        // TODO: value test
    }

    {
        constexpr mat2x2 lhs{1, 1, 1, 1};
        constexpr mat2x2 rhs{1, 1, 1, 1};
        static_assert(lhs == rhs);
    }
}
