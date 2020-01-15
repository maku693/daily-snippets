#include <array>    // array
#include <cassert>  // assert
#include <cmath>    // acos, sqrt
#include <cstddef>  // size_t, ptrdiff_t
#include <iterator> // begin, end

namespace mul_div_ops {

template <class L, class R>
constexpr auto operator*(const L &lhs, const R &rhs) noexcept {
  return L{lhs} *= rhs;
}

template <class L, class R>
constexpr auto operator/(const L &lhs, const R &rhs) noexcept {
  return L{lhs} /= rhs;
}

} // namespace mul_div_ops

namespace vec_ops {

template <class V, class N> constexpr auto operator*=(V &&lhs, N rhs) noexcept {
  for (auto &e : lhs) {
    e *= rhs;
  }
  return lhs;
}

template <class V, class N> constexpr auto operator/=(V &&lhs, N rhs) noexcept {
  for (auto &e : lhs) {
    e /= rhs;
  }
  return lhs;
}

using mul_div_ops::operator*;
using mul_div_ops::operator/;

} // namespace vec_ops

template <class VL, class VR>
constexpr auto dot(const VL &lhs, const VR &rhs) noexcept {
  assert(std::size(lhs) == std::size(rhs));
  L::value_type accum{};
  auto l = std::begin(lhs), r = std::begin(rhs);
  while (l != std::end(lhs)) {
    accum += *l * *r;
    ++l;
    ++r;
  }
  return accum;
}

template <class V> auto norm(const V &v) noexcept {
  return std::sqrt(dot(v, v));
}

template <class V> auto normalize(const V &v) noexcept { return v / norm(v); }

template <class VL, class VR>
auto angle(const VL &lhs, const VR &rhs) noexcept {
  assert(std::size(lhs) == 3 && std::size(lhs) == std::size(rhs));
  return std::acos(dot(normalize(lhs), normalize(rhs)));
}

template <class V> constexpr auto cross(const V &lhs, const V &rhs) {
  assert(std::size(lhs) == 3 && std::size(lhs) == std::size(rhs));
  const auto lx = std::begin(lhs), ly = ++lx, lz = ++ly;
  const auto rx = std::begin(rhs), ry = ++rx, rz = ++ry;
  return {ly * rz - lz * ry, lz * rx - lx * rz, lx * ry - ly * rx};
}

namespace mat_ops {

template <class M> constexpr auto operator*=(M &&lhs, const M &rhs) noexcept {
  auto l = std::begin(lhs), r = std::begin(rhs);
  assert(std::size(lhs) == std::size(*r));
  // TODO:
}

template <class V, class M>
constexpr auto operator*=(V &&lhs, const M &rhs) noexcept {
  auto l = std::begin(lhs), r = std::begin(rhs);
  assert(std::size(lhs) == std::size(*r));
  // TODO:
}

using mul_div_ops::operator*;
using mul_div_ops::operator/;

} // namespace mat_ops

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

template <std::size_t Rows, std::size_t Cols>
constexpr auto identity() noexcept {
  assert(Rows == Cols, "identity matrix is defined only for square matrix");

  M m{};

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

template <std::size_t Rows, std::size_t Cols>
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

template <class Vec, class N> auto make_rotation(const Vec &axis, N theta) {
  const auto x = std::begin(axis), y = ++x, z = ++y;
  const auto st = std::cos(theta);
  const auto ct = std::cos(theta);
  const auto a = (1 - ct);

  return {*x * a + ct,
          *x * *y * a + *y st,
          *x * *z * a + *z st,
          1,
          *y * *x * a + *z st,
          *y * *y * a + ct,
          *y * *z * a + *x st,
          1,
          *z * *x * a + *y st,
          *z * *y * a + *x st,
          *z * *z * a + ct,
          1,
          1,
          1,
          1,
          1};
}

// TODO: scale()

int main() {
  using vec2 = vec<float, 2>;

  {
    constexpr vec<float, 2> v{};
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
