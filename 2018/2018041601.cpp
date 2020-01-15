#include <cstddef>

template <class T, std::size_t Elems>
class mat_row {
    using value_type = T;

    T values[Elems];

    constexpr mat_row() = default;


    constexpr const T& operator[](std::size_t i) const
    {
        return values[i];
    }
};

template <class T, std::size_t Rows, std::size_t Cols>
class mat {
public:
    using value_type = T;
    static constexpr std::size_t rows = Rows;
    static constexpr std::size_t cols = Cols;

    mat_row<T, Cols> values[Rows];

    constexpr mat() = default;

    constexpr const mat_row<T, Cols>& operator[](std::size_t row) const
    {
        return values[row];
    }
    constexpr mat_row<T, Cols>& operator[](std::size_t row)
    {
        return values[row];
    }

    const T* data() const noexcept { return values; }
    T* data() noexcept { return values; }
};

int main()
{
    using mat2x2 = mat<double, 2, 2>;
    constexpr mat2x2 m{{{1.0, 1.0}, {1.0, 1.0}}};
    static_assert(m[0][0] == 1.0);
}
