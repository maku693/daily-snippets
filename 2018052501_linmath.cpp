#include <cmath>
#include <iterator>

namespace detail {

template <class T>
constexpr bool is_nothrow_equatable_v = noexcept(std::declval<T>() !=
                                                 std::declval<T>());

template <class T, class U>
constexpr bool is_nothrow_multipliable_v = noexcept(std::declval<T>() *=
                                                    std::declval<U>());

template <class T, class U>
constexpr bool is_nothrow_dividable_v = noexcept(std::declval<T>() /=
                                                 std::declval<U>());

} // namespace detail

template <class T> struct equatable {
  friend constexpr bool
  operator==(const T &lhs,
             const T &rhs) noexcept(detail::is_nothrow_equatable_v<T>) {
    return !(lhs != rhs);
  }
};

template <class T, class U = T> struct multipliable {
  friend constexpr T
  operator*(const T &lhs,
            const U &rhs) noexcept(detail::is_nothrow_multipliable_v<T, U>) {
    return T{lhs} *= rhs;
  }
};

template <class T, class U = T> struct dividable {
  friend constexpr T
  operator/(const T &lhs,
            const U &rhs) noexcept(detail::is_nothrow_dividable_v<T, U>) {
    return T{lhs} /= rhs;
  }
};

struct vec3;

constexpr float dot(const vec3 &, const vec3 &) noexcept;

struct vec3 : private equatable<vec3>,
              private multipliable<vec3, float>,
              private dividable<vec3, float> {
  float x = 0, y = 0, z = 0;

  constexpr vec3() noexcept = default;
  constexpr vec3(float x, float y, float z) noexcept : x(x), y(y), z(z){};

  constexpr bool operator!=(const vec3 &rhs) const noexcept {
    return x != rhs.x || y != rhs.y || z != rhs.z;
  }

  constexpr vec3 &operator*=(float rhs) noexcept {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  constexpr vec3 &operator/=(float rhs) noexcept {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

  float magnitude() const noexcept { return std::sqrt(dot(*this, *this)); }
};

constexpr float dot(const vec3 &lhs, const vec3 &rhs) noexcept {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

vec3 normalize(const vec3 &v) noexcept { return v / v.magnitude(); }

auto angle(const vec3 &lhs, const vec3 &rhs) noexcept {
  return std::acos(dot(normalize(lhs), normalize(rhs)));
}

constexpr vec3 cross(const vec3 &lhs, const vec3 &rhs) noexcept {
  return {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
          lhs.x * rhs.y - lhs.y * rhs.x};
}

struct mat4 : private equatable<mat4>, private multipliable<mat4> {
  float m[16]{};

  static constexpr std::size_t order = 4;

  constexpr mat4() noexcept = default;

  constexpr float &operator()(const std::size_t row, const std::size_t col) noexcept {
    return m[row * order + col];
  }

  constexpr const float &operator()(const std::size_t row,
                                    const std::size_t col) const noexcept {
    return m[row * order + col];
  }

  constexpr bool operator!=(const mat4 &rhs) const noexcept {
    auto l_it = std::cbegin(m);
    auto r_it = std::cbegin(rhs.m);
    const auto l_end = std::cend(m);
    const auto r_end = std::cbegin(rhs.m);
    while (l_it == l_end && r_it == r_end) {
      if (l_it != r_it) {
        return false;
      }
      ++l_it;
      ++r_it;
    }
    return true;
  }

  constexpr mat4& operator*=(const mat4 &rhs) noexcept {
    const auto [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14,
                m15] = m;
    m[0] = m0 * rhs.m[0] + m4 * rhs.m[1] + m8 * rhs.m[2] + m12 * rhs.m[3];
    m[1] = m1 * rhs.m[0] + m5 * rhs.m[1] + m9 * rhs.m[2] + m13 * rhs.m[3];
    m[2] = m2 * rhs.m[0] + m6 * rhs.m[1] + m10 * rhs.m[2] + m14 * rhs.m[3];
    m[3] = m3 * rhs.m[0] + m7 * rhs.m[1] + m11 * rhs.m[2] + m15 * rhs.m[3];
    m[4] = m0 * rhs.m[4] + m4 * rhs.m[5] + m8 * rhs.m[6] + m12 * rhs.m[7];
    m[5] = m1 * rhs.m[4] + m5 * rhs.m[5] + m9 * rhs.m[6] + m13 * rhs.m[7];
    m[6] = m2 * rhs.m[4] + m6 * rhs.m[5] + m10 * rhs.m[6] + m14 * rhs.m[7];
    m[7] = m3 * rhs.m[4] + m7 * rhs.m[5] + m11 * rhs.m[6] + m15 * rhs.m[7];
    m[8] = m0 * rhs.m[8] + m4 * rhs.m[9] + m8 * rhs.m[10] + m12 * rhs.m[11];
    m[9] = m1 * rhs.m[8] + m5 * rhs.m[9] + m9 * rhs.m[10] + m13 * rhs.m[11];
    m[10] = m2 * rhs.m[8] + m6 * rhs.m[9] + m10 * rhs.m[10] + m14 * rhs.m[11];
    m[11] = m3 * rhs.m[8] + m7 * rhs.m[9] + m11 * rhs.m[10] + m15 * rhs.m[11];
    m[12] = m0 * rhs.m[12] + m4 * rhs.m[13] + m8 * rhs.m[14] + m12 * rhs.m[15];
    m[13] = m1 * rhs.m[12] + m5 * rhs.m[13] + m9 * rhs.m[14] + m13 * rhs.m[15];
    m[14] = m2 * rhs.m[12] + m6 * rhs.m[13] + m10 * rhs.m[14] + m14 * rhs.m[15];
    m[15] = m3 * rhs.m[12] + m7 * rhs.m[13] + m11 * rhs.m[14] + m15 * rhs.m[15];
    return *this;
  }
};

constexpr mat4 transpose(const mat4 &m) noexcept;
constexpr mat4 inverse(const mat4 &m) noexcept;

constexpr mat4 make_identity() noexcept {
  mat4 m{};
  m.m[0] = m.m[5] = m.m[10] = m.m[15] = 1;
  return m;
}

constexpr mat4 make_translate(const vec3 &v) noexcept {
    mat4 m = make_identity();
    m.m[12] = v.x;
    m.m[13] = v.y;
    m.m[14] = v.z;
}

constexpr mat4 make_rotation(const vec3 &v) noexcept;

constexpr mat4 make_scale(const vec3 &v) noexcept {
    mat4 m{};
    m.m[0] = v.x;
    m.m[5] = v.y;
    m.m[10] = v.z;
    m.m[15] = 1;
}

constexpr mat4 make_lookat(const vec3 &from, const vec3 &to,
                           const vec3 &up) noexcept;

constexpr mat4 make_perspective() noexcept;
constexpr mat4 make_orthographic() noexcept;

struct vec4 : private equatable<vec4>, private multipliable<vec4, mat4> {
  float x = 0, y = 0, z = 0, w = 0;

  constexpr vec4() noexcept = default;
  constexpr vec4(float x, float y, float z, float w) noexcept
      : x(x), y(y), z(z), w(w){};
  constexpr vec4(const vec3 &v, float w) noexcept
      : x(v.x), y(v.y), z(v.z), w(w){};

  constexpr bool operator!=(const vec4 &rhs) const noexcept {
    return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
  }

  constexpr vec4 &operator*=(const mat4 &rhs) noexcept {
    const auto [x_, y_, z_, w_] = *this;
    x = x_ * rhs(0, 0) + y_ * rhs(1, 0) + z_ * rhs(2, 0) + w_ * rhs(3, 0);
    y = x_ * rhs(0, 1) + y_ * rhs(1, 1) + z_ * rhs(2, 1) + w_ * rhs(3, 1);
    z = x_ * rhs(0, 2) + y_ * rhs(1, 2) + z_ * rhs(2, 2) + w_ * rhs(3, 2);
    w = x_ * rhs(0, 3) + y_ * rhs(1, 3) + z_ * rhs(2, 3) + w_ * rhs(3, 3);
    return *this;
  }
};

struct quat : private equatable<quat>, private multipliable<quat> {
  float r = 0;
  vec3 v{};

  constexpr quat() noexcept = default;
  constexpr quat(float r, vec3 v) noexcept : r(r), v(v){};

  constexpr auto operator!=(const quat &rhs) const noexcept {
    return r != rhs.r && v != rhs.v;
  }

  constexpr auto operator*=(const quat &rhs) noexcept;
};

int main() {}
