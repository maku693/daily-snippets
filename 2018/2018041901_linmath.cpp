// LDFLAGS="-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib" clang++ --std=c++17 -Wall 20180418.cpp
#include <cstddef>

template <class T, std::size_t N>
class vec {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    T v[N];

    constexpr vec() = default;

    constexpr reference operator[](difference_type i) { return v[i]; }
    constexpr const_reference operator[](difference_type i) const { return v[i]; }

    constexpr size_type size() const noexcept { return N; }

    pointer data() noexcept { return v; }
    const_pointer data() const noexcept { return v; }
};

template <class T, std::size_t N>
constexpr bool operator==(cosnt vec<T, N>& lhs, cosnt vec<T, N>& rhs)
{
    for (std::size_t i = 0; i < N; i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }

    return true;
}

template <class T, std::size_t Rows, std::size_t Cols>
class mat {
public:
    using value_type = T;
    using row_type = vec<T, Cols>;
    using row_reference = row_type&;
    using const_row_reference = const row_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    row_type m[Rows];

    constexpr mat() = default;

    constexpr row_reference operator[](std::size_t i) { return m[i]; }
    constexpr const_row_reference operator[](std::size_t i) const { return m[i]; }

    constexpr size_type rows() const noexcept { return Rows; }
    constexpr size_type cols() const noexcept { return Cols; }

    constexpr size_type size() const noexcept { return Rows * Cols; }

    pointer data() noexcept { return m; }
    const_pointer data() const noexcept { return m; }
};

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
        if (lhs[r] != rhs[r]) {
            return false;
        }
    }

    return true;
}

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

// TODO: constexpr mat<T, 4, 4> persp()
// TODO: constexpr mat<T, 4, 4> ortho()
// TODO: constexpr mat<T, 4, 4> translate(const vec<3>&)
// TODO: constexpr mat<T, 4, 4> rotate(const quaternion&)
// TODO: constexpr mat<T, 4, 4> scale(const vec<3>&)

int main()
{
    using vec2 = vec<float, 2>;

    {
        constexpr vec2 v{};
        static_assert(v[0] == 0);
        static_assert(v[1] == 0);
    }

    {
        constexpr vec2 v{1, 1};
        static_assert(v[0] == 1);
        static_assert(v[1] == 1);
    }

    using mat2x2 = mat<float, 2, 2>;

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
        constexpr mat2x2 expected{1, 2, 3, 4};
        constexpr auto actual = transpose(transpose(expected));
        static_assert(actual[0][0] == expected[0][0]);
        static_assert(actual[0][1] == expected[0][1]);
        static_assert(actual[1][0] == expected[1][0]);
        static_assert(actual[1][1] == expected[1][1]);
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
