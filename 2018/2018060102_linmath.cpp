#include <cmath>
#include <cstddef>
#include <iterator>

namespace detail {

template <class T, class U>
constexpr bool is_nothrow_equatable_v = noexcept(std::declval<T>() ==
                                                 std::declval<T>());

template <class T, class U>
constexpr bool is_nothrow_addable_v = noexcept(std::declval<T>() +=
                                               std::declval<U>());

template <class T, class U>
constexpr bool is_nothrow_subtractable_v = noexcept(std::declval<T>() -=
                                                    std::declval<U>());

template <class T, class U>
constexpr bool is_nothrow_multipliable_v = noexcept(std::declval<T>() *=
                                                    std::declval<U>());

template <class T, class U>
constexpr bool is_nothrow_dividable_v = noexcept(std::declval<T>() /=
                                                 std::declval<U>());

} // namespace detail

template <class T, class U = T> struct equatable {
  friend constexpr bool
  operator!=(const T &lhs,
             const U &rhs) noexcept(detail::is_nothrow_equatable_v<T, U>) {
    return !(lhs == rhs);
  }
};

template <class T, class U = T> struct addable {
  friend constexpr T
  operator+(const T &lhs,
            const U &rhs) noexcept(detail::is_nothrow_addable_v<T, U>) {
    T x{lhs};
    x += rhs;
    return x;
  }
};

template <class T, class U = T> struct subtractable {
  friend constexpr T
  operator-(const T &lhs,
            const U &rhs) noexcept(detail::is_nothrow_subtractable_v<T, U>) {
    T x{lhs};
    x -= rhs;
    return x;
  }
};

template <class T, class U = T> struct multipliable {
  friend constexpr T
  operator*(const T &lhs,
            const U &rhs) noexcept(detail::is_nothrow_multipliable_v<T, U>) {
    T x{lhs};
    x *= rhs;
    return x;
  }
};

template <class T, class U = T> struct dividable {
  friend constexpr T
  operator/(const T &lhs,
            const U &rhs) noexcept(detail::is_nothrow_dividable_v<T, U>) {
    T x{lhs};
    x /= rhs;
    return x;
  }
};

struct vec3;

constexpr float dot(const vec3 &, const vec3 &) noexcept;

struct vec3 : private equatable<vec3>,
              private addable<vec3>,
              private subtractable<vec3>,
              private multipliable<vec3, float>,
              private dividable<vec3, float> {
  float x{}, y{}, z{};

  constexpr vec3() noexcept = default;
  constexpr vec3(float x, float y, float z) noexcept : x(x), y(y), z(z){};

  constexpr bool operator==(const vec3 &rhs) const noexcept {
    return x == rhs.x && y == rhs.y && z == rhs.z;
  }

  constexpr vec3 &operator+=(const vec3 &rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  constexpr vec3 &operator-=(const vec3 &rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  constexpr vec3 &operator*=(const float rhs) noexcept {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  constexpr vec3 &operator/=(const float rhs) noexcept {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

  constexpr float squared_magnitude() const noexcept {
    return dot(*this, *this);
  }

  float magnitude() const noexcept { return std::sqrt(squared_magnitude()); }
};

constexpr float dot(const vec3 &lhs, const vec3 &rhs) noexcept {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

vec3 normalize(const vec3 &v) noexcept {
  return v / v.magnitude();
}

auto angle(const vec3 &lhs, const vec3 &rhs) noexcept {
  return std::acos(dot(normalize(lhs), normalize(rhs)));
}

constexpr vec3 cross(const vec3 &lhs, const vec3 &rhs) noexcept {
  return {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
          lhs.x * rhs.y - lhs.y * rhs.x};
}

struct vec4 : private equatable<vec4> {
  float x{}, y{}, z{}, w{};

  constexpr vec4() noexcept = default;
  constexpr vec4(float x, float y, float z, float w) noexcept
      : x(x), y(y), z(z), w(w){};

  constexpr bool operator==(const vec4 &rhs) const noexcept {
    return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
  }
};

struct mat4 : private equatable<mat4> {
  float m[16]{};

  constexpr mat4() noexcept = default;
  constexpr mat4(float m0, float m1, float m2, float m3, float m4, float m5,
                 float m6, float m7, float m8, float m9, float m10, float m11,
                 float m12, float m13, float m14, float m15) noexcept
      : m{m0, m1, m2,  m3,  m4,  m5,  m6,  m7,
          m8, m9, m10, m11, m12, m13, m14, m15} {}

  constexpr bool operator==(const mat4 &rhs) const noexcept {
    auto l = std::cbegin(m);
    auto r = std::cbegin(rhs.m);
    const auto l_last = std::cend(m);
    for (; l != l_last; l++, r++) {
      if (*l != *r) {
        return false;
      }
    }
    return true;
  }

  constexpr float &operator[](std::size_t i) noexcept { return m[i]; };
  constexpr const float &operator[](std::size_t i) const noexcept {
    return m[i];
  };
};

constexpr mat4 operator*(const mat4 &lhs, const mat4 &rhs) noexcept {
  mat4 m;
  for (std::size_t c = 0; c < 4; c++) {
    for (std::size_t r = 0; r < 4; r++) {
      float f{};
      for (std::size_t i = 0; i < 4; i++) {
        f += lhs.m[i * 4 + r] * rhs.m[c * 4 + i];
      }
      m[c * 4 + r] = f;
    }
  }
  return m;
}

constexpr vec4 operator*(const mat4 &lhs, const vec4 &rhs) noexcept {
  return {lhs[0] * rhs.x + lhs[4] * rhs.y + lhs[8] * rhs.z + lhs[12] * rhs.w,
          lhs[1] * rhs.x + lhs[5] * rhs.y + lhs[9] * rhs.z + lhs[13] * rhs.w,
          lhs[2] * rhs.x + lhs[6] * rhs.y + lhs[10] * rhs.z + lhs[14] * rhs.w,
          lhs[3] * rhs.x + lhs[7] * rhs.y + lhs[11] * rhs.z + lhs[15] * rhs.w};
}

constexpr mat4 make_identity() noexcept {
  mat4 x{};
  x[0] = x[5] = x[10] = x[15] = 1;
  return x;
}

constexpr mat4 make_translate(const vec3 &v) noexcept {
  mat4 x = make_identity();
  x[12] = v.x;
  x[13] = v.y;
  x[14] = v.z;
  return x;
}

mat4 make_rotation(const vec3 &v) noexcept;

mat4 make_scale(const vec3 &v) noexcept {
  mat4 x{};
  x[0] = v.x;
  x[5] = v.y;
  x[10] = v.z;
  x[15] = 1;
  return x;
}

mat4 make_perspective(float fovy, float aspect, float near,
                      float far) noexcept {
  const float a = 1 / std::tan(fovy / 2);
  const float b = 1 / (near - far);
  mat4 x{};
  x[0] = a / aspect;
  x[5] = a;
  x[10] = (near + far) * b;
  x[11] = near * far * b * 2;
  return x;
}

struct quat : private equatable<quat>, private multipliable<quat> {
  float r{};
  vec3 v{};

  constexpr quat() noexcept = default;
  constexpr quat(float r, vec3 v) noexcept : r(r), v(v){};

  constexpr bool operator!=(const quat &rhs) const noexcept {
    return r != rhs.r || v != rhs.v;
  }

  quat &operator*=(const quat &rhs) noexcept {
    const auto r_ = r;
    const auto v_ = v;
    r = r_ * rhs.r - dot(v_, rhs.v);
    v = v_ * rhs.r + rhs.v * r_ + cross(v_, rhs.v);
    return *this;
  }

  float magnitude() const noexcept {
    return std::sqrt(r * r + v.squared_magnitude());
  }
};

quat make_from_eular(const vec3 &axis, const float angle) noexcept {
  const float a = angle / 2;
  const float sin_a = std::sin(a);
  return {std::cos(a),
          {
              axis.x * sin_a,
              axis.y * sin_a,
              axis.z * sin_a,
          }};
}

mat4 to_rotation_mat4(const quat &q) noexcept {
  const float xx = q.v.x * q.v.x;
  const float xy = q.v.x * q.v.y;
  const float xz = q.v.x * q.v.z;
  const float yy = q.v.y * q.v.y;
  const float yz = q.v.y * q.v.z;
  const float zz = q.v.z * q.v.z;
  const float xr = q.v.x * q.r;
  const float yr = q.v.y * q.r;
  const float zr = q.v.z * q.r;
  return mat4{1 - 2 * (yy + zz),
              2 * (xy - zr),
              2 * (xz + yr),
              0,
              2 * (xy + zr),
              1 - 2 * (xx + zz),
              2 * (yz - xr),
              0,
              2 * (xz - yr),
              2 * (yz + xr),
              1 - 2 * (xx + yy),
              0,
              0,
              0,
              0,
              1};
}

mat4 make_rotation(const vec3 &v) noexcept {
  const auto qx = make_from_eular({1, 0, 0}, v.x);
  const auto qy = make_from_eular({0, 1, 0}, v.y);
  const auto qz = make_from_eular({0, 0, 1}, v.z);
  return to_rotation_mat4(qx * qy * qx);
}

#include <cassert>
#include <cmath>
#include <iostream>

int main() {
  {
    constexpr vec4 v{1, 2, 3, 4};
    static_assert(make_identity() * v == v);
  }

  {
    constexpr mat4 m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    static_assert(make_identity() * m == m);
  }

  {
    constexpr vec4 expected{2, 4, 6, 1};
    constexpr auto actual = make_translate({1, 2, 3}) * vec4{1, 2, 3, 1};
    static_assert(actual == expected);
  }

  {
    const float pi = std::acos(-1);
    const auto v = make_rotation(vec3{0, pi, 0}) * vec4{1, 0, 0, 1};
    std::cout << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << '\n';
  }
}
