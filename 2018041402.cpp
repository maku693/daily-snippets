#include <cstddef>
#include <initializer_list>

template <class T, std::size_t Rows, std::size_t Cols>
class matrix {
public:
    using value_type = T;
    static constexpr std::size_t rows = Rows;
    static constexpr std::size_t cols = Cols;

    constexpr matrix() = default;

    template <class ...Ts>
    constexpr matrix(Ts ...args) : m{args...} {}

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

private:
    T m[Rows][Cols];
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
constexpr bool is_multiplicable = L::cols == R::rows;

template <class L, class R>
constexpr auto operator *= (L& lhs, const R& rhs)
{
    using T = typename L::value_type;
    constexpr std::size_t Rows = R::rows;
    constexpr std::size_t Cols = L::cols;

    for (std::size_t r = 0; r < Rows; r++) {
        for (std::size_t c = 0; c < Cols; c++) {
            T v;
            for (std::size_t i = 0; i < Cols; i++) {
                v += lhs(r, i) * rhs(i, c);
            }
            lhs(r, c) = v;
        }
    }

    return lhs;
}

template <class L, class R>
constexpr auto operator * (const L& lhs, const R& rhs) noexcept
{
    return matrix<typename L::value_type, L::rows, L::cols>{ lhs } *= rhs;
}

int main()
{
    using mat3x3 = matrix<double, 3, 3>;
    using mat2x2 = matrix<double, 2, 2>;

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
        constexpr mat2x2 m{1.0, 1.0, 1.0, 1.0};
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
        static_assert(is_multiplicable<mat2x2, mat2x2>);
        static_assert(!is_multiplicable<mat2x2, mat3x3>);
    }

    {
        // Operators
    }
}
