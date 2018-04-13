#include <cstddef>

template <class T, std::size_t Rows, std::size_t Cols>
class matrix {
public:
    static constexpr std::size_t rows = Rows;
    static constexpr std::size_t cols = Cols;

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
            if (r != c) continue;
            m(r, c) = 1;
        }
    }

    return m;
}

#include <iostream>

int main()
{
    constexpr auto m = make_identity<double, 2, 2>();
    std::cout <<
        m(0, 0) << ',' <<
        m(0, 1) << ',' <<
        m(1, 0) << ',' <<
        m(1, 1) << '\n';
}

