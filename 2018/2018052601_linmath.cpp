#include <cmath>
#include <iterator>

namespace detail {

template <class T, class U>
constexpr bool is_nothrow_equatable_v = noexcept(std::declval<T>() !=
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
  operator==(const T &lhs,
             const U &rhs) noexcept(detail::is_nothrow_equatable_v<T, U>) {
    return !(lhs != rhs);
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

  constexpr bool operator!=(const vec3 &rhs) const noexcept {
    return x != rhs.x || y != rhs.y || z != rhs.z;
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

  static constexpr std::size_t order{4};

  constexpr mat4() noexcept = default;
  constexpr mat4(float m0, float m1, float m2, float m3, float m4, float m5,
                 float m6, float m7, float m8, float m9, float m10, float m11,
                 float m12, float m13, float m14, float m15)
      : m{m0, m1, m2,  m3,  m4,  m5,  m6,  m7,
          m8, m9, m10, m11, m12, m13, m14, m15} {}

  constexpr float &operator()(const std::size_t col,
                              const std::size_t row) noexcept {
    return m[row * order + col];
  }

  constexpr const float &operator()(const std::size_t col,
                                    const std::size_t row) const noexcept {
    return m[row * order + col];
  }

  constexpr bool operator!=(const mat4 &rhs) const noexcept {
    auto l_iter = std::cbegin(m);
    auto r_iter = std::cbegin(rhs.m);
    const auto l_end = std::cend(m);
    const auto r_end = std::cbegin(rhs.m);
    while (l_iter == l_end && r_iter == r_end) {
      if (l_iter != r_iter) {
        return false;
      }
      ++l_iter;
      ++r_iter;
    }
    return true;
  }

  constexpr mat4 &operator*=(const mat4 &rhs) noexcept {
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

constexpr mat4 make_identity() noexcept {
  mat4 x{};
  x(0, 0) = x(1, 1) = x(2, 2) = x(3, 3) = 1;
  return x;
}

constexpr mat4 make_translate(const vec3 &v) noexcept {
  mat4 x = make_identity();
  x(0, 3) = v.x;
  x(1, 3) = v.y;
  x(2, 3) = v.z;
  return x;
}

mat4 make_rotation(const vec3 &v) noexcept;

constexpr mat4 make_scale(const vec3 &v) noexcept {
  mat4 x{};
  x(0, 0) = v.x;
  x(1, 1) = v.y;
  x(2, 2) = v.z;
  x(3, 3) = 1;
  return x;
}

mat4 make_perspective(float fovy, float aspect, float near,
                      float far) noexcept {
  const float a = 1 / std::tan(fovy / 2);
  const float b = 1 / (near - far);
  mat4 x{};
  x(0, 0) = a / aspect;
  x(1, 1) = a;
  x(2, 2) = (near + far) * b;
  x(2, 3) = near * far * b * 2;
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

quat make_from_eular(const vec3 &rotation) noexcept {
  const float angle = rotation.magnitude();
  const vec3 normal = normalize(rotation);
  const float half_sin_theta = std::sin(angle) / 2;
  return quat{std::cos(angle) / 2,
              {
                  normal.x * half_sin_theta,
                  normal.y * half_sin_theta,
                  normal.z * half_sin_theta,
              }};
}

mat4 to_rotation_mat4(const quat &q) noexcept {
  const float a = std::pow(q.magnitude(), -2) * 2;
  const float b = 1 - a;
  const float xx = q.v.x * q.v.x;
  const float xy = q.v.x * q.v.y;
  const float xz = q.v.x * q.v.z;
  const float yy = q.v.y * q.v.y;
  const float yz = q.v.y * q.v.z;
  const float zz = q.v.z * q.v.z;
  const float xr = q.v.x * q.r;
  const float yr = q.v.y * q.r;
  const float zr = q.v.z * q.r;
  return mat4{b * (yy + zz),
              a * (xy - zr),
              a * (xz + yr),
              1,
              a * (xy + zr),
              b * (xx + zz),
              a * (yz - xr),
              1,
              a * (xz - yr),
              a * (yz + xr),
              b * (xx + yy),
              1,
              1,
              1,
              1,
              1};
}

mat4 make_rotation(const vec3 &v) noexcept {
  return to_rotation_mat4(make_from_eular(v));
}

int main() {}
