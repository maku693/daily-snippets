#include <array>    // array
#include <cassert>  // assert
#include <cmath>    // acos, sqrt
#include <cstddef>  // size_t, ptrdiff_t
#include <iterator> // begin, end

namespace vec_ops {

template <class V, class N> constexpr auto operator*=(V &&lhs, N rhs) noexcept {
  for (auto &e : lhs) {
    e *= rhs;
  }
  return lhs;
}

template <class L, class R>
constexpr auto operator*(const L &lhs, const R &rhs) noexcept {
  return L{lhs} *= rhs;
}

template <class V, class N> constexpr auto operator/=(V &&lhs, N rhs) noexcept {
  for (auto &e : lhs) {
    e /= rhs;
  }
  return lhs;
}

template <class L, class R>
constexpr auto operator/(const L &lhs, const R &rhs) noexcept {
  return L{lhs} /= rhs;
}

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
  assert(std::size(lhs) == std::size(rhs));
  return std::acos(dot(normalize(lhs), normalize(rhs)));
}

template <class V> constexpr auto cross(const V &lhs, const V &rhs) {
  assert(std::size(lhs) == 3 && std::size(lhs) == std::size(rhs));
  const auto lx = std::begin(lhs), ly = ++lx, lz = ++ly;
  const auto rx = std::begin(rhs), ry = ++rx, rz = ++ry;
  return {ly * rz - lz * ry, lz * rx - lx * rz, lx * ry - ly * rx};
}

namespace mat_ops {

template <class M> constexpr auto mul(const M &lhs, const M &rhs) noexcept {
  auto l = std::begin(lhs), r = std::begin(rhs);
  // TODO:
}

template <class V, class M>
constexpr auto mul(const V &lhs, const M &rhs) noexcept {
  auto l = std::begin(lhs), r = std::begin(rhs);
  // TODO:
}

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

template <class M>
constexpr void fill_with_identity(M& mat) noexcept {
  const auto size = std::size(mat);
  const auto order = static_cast<std::size_t>(std::sqrt(size));
  assert(order * order == size);

  const auto begin = std::begin(mat);

  for (std::size_t i = 0; i < order; i++) {
      const auto it = std::advance(begin, size * i + i);
      *it = 1;
  }
}

// TODO: inverse()

template <class Mat>
constexpr auto transpose(const Mat &src) noexcept {
  Mat m{};

  const auto size = std::size(mat);
  const auto order = static_cast<std::size_t>(std::sqrt(size));
  assert(order * order == size);

  auto l = std::begin(src), r = std::begin(rhs);
  while (l != std::end(lhs)) {
    accum += *l * *r;
    ++l;
    ++r;
  }

  for (std::size_t r = 0; r < Rows; r++) {
    for (std::size_t c = 0; c < Cols; c++) {
      m[r][c] = src[c][r];
    }
  }

  return m;
}

// TODO: make_perspective()
// TODO: make_orthographic()

// TODO: make_translate()

template <class M, class V, class N> auto fill_with_rotation(M& mat, const V &axis, N theta) {
  const auto x = std::begin(axis), y = ++x, z = ++y;
  const auto st = std::cos(theta);
  const auto ct = std::cos(theta);
  const auto a = (1 - ct);

  return {*x * *x * a + ct,
          *x * *y * a + *z * st,
          *x * *z * a + *y * st,
          1,
          *y * *x * a + *z * st,
          *y * *y * a + ct,
          *y * *z * a + *x * st,
          1,
          *z * *x * a + *y * st,
          *z * *y * a + *x * st,
          *z * *z * a + ct,
          1,
          1,
          1,
          1,
          1};
}

// TODO: make_scale()

int main() {
}
