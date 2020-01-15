#include <cmath>
#include <cstddef>
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

struct vec4 : private equatable<vec4>, private multipliable<vec4, mat4> {
  float x{}, y{}, z{}, w{};

  constexpr vec4() noexcept = default;
  constexpr vec4(float x, float y, float z, float w) noexcept
      : x(x), y(y), z(z), w(w){};
  constexpr vec4(const vec3 &v, float w) noexcept : vec4{v.x, v.y, v.z, w} {};

  constexpr bool operator!=(const vec4 &rhs) const noexcept {
    return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
  }

  constexpr float &operator[](std::size_t i) noexcept {
    return reinterpret_cast<float *>(this)[i];
  };
  constexpr const float &operator[](std::size_t i) const noexcept {
    return reinterpret_cast<const float *>(this)[i];
  };
};

struct mat4 : private equatable<mat4>, private multipliable<mat4> {
  vec4 data[4]{};

  static constexpr std::size_t order{4};

  constexpr mat4() noexcept = default;
  constexpr mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3) noexcept
      : data{col0, col1, col2, col3} {};
  constexpr mat4(float f0, float f1, float f2, float f3, float f4, float f5,
                 float f6, float f7, float f8, float f9, float f10, float f11,
                 float f12, float f13, float f14, float f15) noexcept
      : mat4{{f0, f1, f2, f3},
             {f4, f5, f6, f7},
             {f8, f9, f10, f11},
             {f12, f13, f14, f15}} {}

  constexpr bool operator!=(const mat4 &rhs) const noexcept {
    return data[0] != rhs.data[0] || data[1] != rhs.data[1] ||
           data[2] != rhs.data[2] || data[3] != rhs.data[3];
  }

  constexpr mat4 &operator*=(const mat4 &rhs) noexcept {
    float m00 = data[0][0] * rhs[0][0] + data[1][0] * rhs[0][1] +
                data[2][0] * rhs[0][2] + data[3][0] * rhs[0][3];
    float m10 = data[0][0] * rhs[1][0] + data[1][0] * rhs[1][1] +
                data[2][0] * rhs[1][2] + data[3][0] * rhs[1][3];
    float m20 = data[0][0] * rhs[2][0] + data[1][0] * rhs[2][1] +
                data[2][0] * rhs[2][2] + data[3][0] * rhs[2][3];
    float m30 = data[0][0] * rhs[3][0] + data[1][0] * rhs[3][1] +
                data[2][0] * rhs[3][2] + data[3][0] * rhs[3][3];
    float m01 = data[0][1] * rhs[0][0] + data[1][1] * rhs[0][1] +
                data[2][1] * rhs[0][2] + data[3][1] * rhs[0][3];
    float m11 = data[0][1] * rhs[1][0] + data[1][1] * rhs[1][1] +
                data[2][1] * rhs[1][2] + data[3][1] * rhs[1][3];
    float m21 = data[0][1] * rhs[2][0] + data[1][1] * rhs[2][1] +
                data[2][1] * rhs[2][2] + data[3][1] * rhs[2][3];
    float m31 = data[0][1] * rhs[3][0] + data[1][1] * rhs[3][1] +
                data[2][1] * rhs[3][2] + data[3][1] * rhs[3][3];
    float m02 = data[0][2] * rhs[0][0] + data[1][2] * rhs[0][1] +
                data[2][2] * rhs[0][2] + data[3][2] * rhs[0][3];
    float m12 = data[0][2] * rhs[1][0] + data[1][2] * rhs[1][1] +
                data[2][2] * rhs[1][2] + data[3][2] * rhs[1][3];
    float m22 = data[0][2] * rhs[2][0] + data[1][2] * rhs[2][1] +
                data[2][2] * rhs[2][2] + data[3][2] * rhs[2][3];
    float m32 = data[0][2] * rhs[3][0] + data[1][2] * rhs[3][1] +
                data[2][2] * rhs[3][2] + data[3][2] * rhs[3][3];
    float m03 = data[0][3] * rhs[0][0] + data[1][3] * rhs[0][1] +
                data[2][3] * rhs[0][2] + data[3][3] * rhs[0][3];
    float m13 = data[0][3] * rhs[1][0] + data[1][3] * rhs[1][1] +
                data[2][3] * rhs[1][2] + data[3][3] * rhs[1][3];
    float m23 = data[0][3] * rhs[2][0] + data[1][3] * rhs[2][1] +
                data[2][3] * rhs[2][2] + data[3][3] * rhs[2][3];
    float m33 = data[0][3] * rhs[3][0] + data[1][3] * rhs[3][1] +
                data[2][3] * rhs[3][2] + data[3][3] * rhs[3][3];

    m00 = data[0][0];
    m10 = data[1][0];
    m20 = data[2][0];
    m30 = data[3][0];
    m01 = data[0][1];
    m11 = data[1][1];
    m21 = data[2][1];
    m31 = data[3][1];
    m02 = data[0][2];
    m12 = data[1][2];
    m22 = data[2][2];
    m32 = data[3][2];
    m03 = data[0][3];
    m13 = data[1][3];
    m23 = data[2][3];
    m33 = data[3][3];

    return *this;
  }

  constexpr vec4 &operator[](std::size_t i) noexcept { return data[i]; };
  constexpr const vec4 &operator[](std::size_t i) const noexcept {
    return data[i];
  };
};

constexpr vec4 &operator*(const mat4 &lhs, const vec4 &rhs) noexcept {
  const float x_ = rhs.x;
  const float y_ = rhs.y;
  const float z_ = rhs.z;
  const float w_ = rhs.w;
  return {lhs[0][0] * x_ + lhs[1][0] * y_ + lhs[2][0] * z_ + lhs[3][0] * w_,
          lhs[0][1] * x_ + lhs[1][1] * y_ + lhs[2][1] * z_ + lhs[3][1] * w_,
          lhs[0][2] * x_ + lhs[1][2] * y_ + lhs[2][2] * z_ + lhs[3][2] * w_,
          lhs[0][3] * x_ + lhs[1][3] * y_ + lhs[2][3] * z_ + lhs[3][3] * w_};
}

constexpr mat4 make_identity() noexcept {
  mat4 x{};
  x[0][0] = x[1][1] = x[2][2] = x[3][3] = 1;
  return x;
}

constexpr mat4 make_translate(const vec3 &v) noexcept {
  mat4 x = make_identity();
  x[0][3] = v.x;
  x[1][3] = v.y;
  x[2][3] = v.z;
  return x;
}

mat4 make_rotation(const vec3 &v) noexcept;

constexpr mat4 make_scale(const vec3 &v) noexcept {
  mat4 x{};
  x[0][0] = v.x;
  x[1][1] = v.y;
  x[2][2] = v.z;
  x[3][3] = 1;
  return x;
}

mat4 make_perspective(float fovy, float aspect, float near,
                      float far) noexcept {
  const float a = 1 / std::tan(fovy / 2);
  const float b = 1 / (near - far);
  mat4 x{};
  x[0][0] = a / aspect;
  x[1][1] = a;
  x[2][2] = (near + far) * b;
  x[2][3] = near * far * b * 2;
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
