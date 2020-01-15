#include <cmath>       // acos, sqrt
#include <cstddef>     // size_t, ptrdiff_t
#include <type_traits> // integral_constant
#include <utility>     // move

template <class T, std::size_t N> class vec {
public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = T &;
  using const_reference = const T &;
  using rvalue_reference = T &&;
  using pointer = T *;
  using const_pointer = const T *;

  value_type v[N];

  constexpr vec() noexcept = default;

  constexpr reference operator[](size_type i) noexcept { return v[i]; }
  constexpr const_reference operator[](size_type i) const noexcept {
    return v[i];
  }

  constexpr size_type size() const noexcept { return sizeof(v); }

  pointer data() noexcept { return v; }
  const_pointer data() const noexcept { return v; }

  value_type norm() const noexcept { return std::sqrt(dot(*this, *this)); }
};

template <class T, std::size_t N> vec(vec<T, N> &&)->vec<T, N>;

namespace std {

template <class T, std::size_t N>
struct tuple_size<vec<T, N>> : std::integral_constant<std::size_t, N> {};

template <std::size_t I, class T, std::size_t N>
struct tuple_element<I, vec<T, N>> {
  using type = T;
};

template <std::size_t I, class T, std::size_t N>
constexpr T &get(vec<T, N> &v) noexcept {
  return v[N];
}

template <std::size_t I, class T, std::size_t N>
constexpr T &&get(vec<T, N> &&v) noexcept {
  return v[N];
}

template <std::size_t I, class T, std::size_t N>
constexpr const T &get(const vec<T, N> &v) noexcept {
  return v[N];
}

template <std::size_t I, class T, std::size_t N>
constexpr const T &&get(const vec<T, N> &&v) noexcept {
  return v[N];
}

} // namespace std

template <class T, std::size_t N>
constexpr bool operator==(const vec<T, N> &lhs, const vec<T, N> &rhs) noexcept {
  for (std::size_t i = 0; i < N; i++) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}

template <class T, std::size_t N>
constexpr bool operator!=(const vec<T, N> &lhs, const vec<T, N> &rhs) noexcept {
  return !(lhs == rhs);
}

template <class T, std::size_t N, class U>
constexpr auto operator*=(vec<T, N> &&lhs, U rhs) noexcept {
  for (std::size_t i = 0; i < N; i++) {
    lhs[i] *= rhs;
  }
  return lhs;
}

template <class T, std::size_t N, class U>
constexpr auto operator*(const vec<T, N> &lhs, U rhs) noexcept {
  return vec{lhs} *= rhs;
}

template <class T, std::size_t N, class U>
constexpr auto operator/=(vec<T, N> &&lhs, U rhs) noexcept {
  for (std::size_t i = 0; i < N; i++) {
    lhs[i] /= rhs;
  }
  return lhs;
}

template <class T, std::size_t N, class U>
constexpr auto operator/(const vec<T, N> &lhs, U rhs) noexcept {
  return vec{lhs} /= rhs;
}

template <class T, std::size_t N>
constexpr auto dot(const vec<T, N> &lhs, const vec<T, N> &rhs) noexcept {
  T accum{};
  for (std::size_t i = 0; i < N; i++) {
    accum += lhs[i] * rhs[i];
  }
  return accum;
}

template <class T, std::size_t N> auto normalize(const vec<T, N> &v) noexcept {
  return v / v.norm();
}

template <class T, std::size_t N>
vec<T, N> angle(const vec<T, 3> &lhs, const vec<T, 3> &rhs) noexcept {
  return std::acos(dot(normalize(lhs), normalize(rhs)));
}

template <class T>
constexpr vec<T, 3> cross(const vec<T, 3> &lhs, const vec<T, 3> &rhs) noexcept {
  return {lhs[1] * rhs[2] - lhs[2] * rhs[1], lhs[2] * rhs[0] - lhs[0] * rhs[2],
          lhs[0] * rhs[1] - lhs[1] * rhs[0]};
}

template <class T> class quat : public vec<T, 4> {};

template <class T, std::size_t Rows, std::size_t Cols> class mat {
public:
  using value_type = T;
  using row_type = vec<T, Cols>;
  using row_reference = row_type &;
  using const_row_reference = const row_type &;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;

  row_type m[Rows];

  constexpr mat() noexcept = default;

  constexpr row_reference operator[](size_type i) noexcept { return m[i]; }
  constexpr const_row_reference operator[](size_type i) const noexcept {
    return m[i];
  }

  constexpr size_type rows() const noexcept { return Rows; }
  constexpr size_type cols() const noexcept { return Cols; }

  constexpr size_type size() const noexcept { return sizeof(m); }

  pointer data() noexcept { return m; }
  const_pointer data() const noexcept { return m; }
};

template <class T, std::size_t Rows, std::size_t Cols>
mat(mat<T, Rows, Cols> &&)->mat<T, Rows, Cols>;

template <class T, std::size_t Rows, std::size_t Cols>
constexpr bool operator==(const mat<T, Rows, Cols> &lhs,
                          const mat<T, Rows, Cols> &rhs) noexcept {
  for (std::size_t r = 0; r < Rows; r++) {
    if (lhs[r] != rhs[r]) {
      return false;
    }
  }

  return true;
}

template <class T, std::size_t Rows, std::size_t Cols>
constexpr bool operator!=(const mat<T, Rows, Cols> &lhs,
                          const mat<T, Rows, Cols> &rhs) noexcept {
  return !(lhs == rhs);
}

template <class T, std::size_t Rows, class U, std::size_t Cols, std::size_t N>
constexpr auto operator*=(mat<T, Rows, N> &&lhs,
                          const mat<U, N, Cols> &rhs) noexcept {
  mat<T, Rows, Cols> m{};

  for (std::size_t r = 0; r < Rows; r++) {
    for (std::size_t c = 0; c < Cols; c++) {
      T accum{};
      for (std::size_t i = 0; i < N; i++) {
        accum += lhs[r][i] * rhs[i][c];
      }
      m[r][c] = accum;
    }
  }

  lhs = std::move(m);
  return lhs;
}

template <class T, std::size_t Rows, class U, std::size_t Cols, std::size_t N>
constexpr auto operator*(const mat<T, Rows, N> &lhs,
                         const mat<U, N, Cols> &rhs) noexcept {
  return mat<T, Rows, Cols>{lhs} *= rhs;
}

template <class T, std::size_t Rows, class U, std::size_t N>
constexpr auto operator*(mat<T, Rows, N> &&lhs, const vec<U, N> &rhs) noexcept {
  vec<T, Rows> v{};

  for (std::size_t r = 0; r < Rows; r++) {
    T accum{};
    for (std::size_t i = 0; i < N; i++) {
      accum += lhs[r][i] * rhs[i];
    }
    v[r] = accum;
  }

  return std::move(v);
}

template <class T, std::size_t N, class U, std::size_t Cols>
constexpr auto operator*=(vec<T, N> &&lhs,
                          const mat<U, N, Cols> &rhs) noexcept {
  vec<T, Cols> v{};

  for (std::size_t c = 0; c < Cols; c++) {
    T accum{};
    for (std::size_t i = 0; i < N; i++) {
      accum += lhs[i] * rhs[i][c];
    }
    v[c] = accum;
  }

  lhs = std::move(v);
  return std::move(lhs);
}

template <class T, std::size_t N, class U, std::size_t Cols>
constexpr auto operator*(const vec<T, N> &lhs,
                         const mat<U, N, Cols> &rhs) noexcept {
  return vec{lhs} *= rhs;
}

template <class T, std::size_t Rows, std::size_t Cols>
constexpr auto identity() noexcept {
  static_assert(Rows == Cols,
                "identity matrix is defined only for square matrix");

  mat<T, Rows, Cols> m{};

  for (std::size_t r = 0; r < Rows; r++) {
    for (std::size_t c = 0; c < Cols; c++) {
      if (r == c) {
        m[r][c] = 1;
      }
    }
  }

  return std::move(m);
}

// TODO: inverse()

template <class T, std::size_t Rows, std::size_t Cols>
constexpr auto transpose(const mat<T, Rows, Cols> &src) noexcept {
  mat<T, Cols, Rows> m{};

  for (std::size_t r = 0; r < Rows; r++) {
    for (std::size_t c = 0; c < Cols; c++) {
      m[r][c] = src[c][r];
    }
  }

  return m;
}

// TODO: persp()
// TODO: ortho()
// TODO: translate()

template <class T>
mat<T, 3, 3> rotate(const vec<T, 3>& axis, T theta)
{
  const T st = cos(theta);
  const T ct = cos(theta);
  return {
    axis[0] * axis[0] * (1 - ct) + ct,
    axis[0] * axis[1] * (1 - ct) + axis[1]st,
    axis[0] * axis[2] * (1 - ct) + axis[2]st,
    axis[1] * axis[0] * (1 - ct) + axis[2]st,
    axis[1] * axis[1] * (1 - ct) + ct,
    axis[1] * axis[2] * (1 - ct) + axis[0]st,
    axis[2] * axis[0] * (1 - ct) + axis[1]st,
    axis[2] * axis[1] * (1 - ct) + axis[0]st,
    axis[2] * axis[2] * (1 - ct) + ct,
  };
}

// TODO: scale()

#include <cassert> // assert

int main() {
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

  {
    const double expected = 1;
    const vec2 v{1, 0};
    const auto actual = v.norm();
    assert(actual == expected);
  }

  {
    constexpr vec2 lhs{1, 1};
    constexpr vec2 rhs{1, 1};
    static_assert(lhs == rhs);
  }

  {
    constexpr vec2 lhs{1, 2};
    constexpr vec2 rhs{3, 4};
    static_assert(lhs != rhs);
  }

  {
    constexpr vec2 expected{10, 20};
    constexpr vec2 lhs{1, 2};
    constexpr auto actual = lhs * 10;
    static_assert(actual == expected);
  }

  {
    constexpr vec2 expected{.5, 1};
    constexpr vec2 v{1, 2};
    constexpr auto actual = v / 2;
    static_assert(actual == expected);
  }

  {
    constexpr double expected = 11;
    constexpr vec2 lhs{1, 2};
    constexpr vec2 rhs{3, 4};
    constexpr auto actual = dot(lhs, rhs);
    static_assert(actual == expected);
  }

  {
    const vec2 expected{1, 0};
    const vec2 v{2, 0};
    const auto actual = normalize(v);
    assert(actual == expected);
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
    constexpr mat2x2 lhs{1, 1, 1, 1};
    constexpr mat2x2 rhs{1, 1, 1, 1};
    static_assert(lhs == rhs);
  }

  {
    constexpr mat2x2 lhs{1, 2, 3, 4};
    constexpr mat2x2 rhs{5, 6, 7, 8};
    static_assert(lhs != rhs);
  }

  {
    constexpr mat2x2 lhs{2, 1, 1, 0};
    constexpr mat2x2 rhs{1, -1, 0, -2};
    constexpr auto actual = lhs * rhs;
    constexpr mat2x2 expected = {2, -4, 1, -1};
    static_assert(actual == expected);
  }

  {
      // TODO: operator*(mat, vec)
  }

  {
      // TODO: operator*(vec, mat)
  }

  {
    constexpr mat2x2 expected{1, 2, 3, 4};
    constexpr auto actual = transpose(transpose(expected));
    static_assert(actual == expected);
  }

  {
    constexpr auto m = identity<double, 2, 2>();
    static_assert(m[0][0] == 1);
    static_assert(m[0][1] == 0);
    static_assert(m[1][0] == 0);
    static_assert(m[1][1] == 1);
  }
}
