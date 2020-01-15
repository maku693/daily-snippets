#include <cmath>
#include <iterator>

namespace detail {

template <class T>
constexpr bool is_nothrow_equatable_v = noexcept(std::declval<T>() !=
                                                 std::declval<T>());

template <class T, class U = T>
constexpr bool is_nothrow_multipliable_v = noexcept(std::declval<T>() *=
                                                    std::declval<U>());

template <class T, class U = T>
constexpr bool is_nothrow_dividable_v = noexcept(std::declval<T>() !=
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

struct mat4;

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

  constexpr vec4 &operator*=(const mat4 &rhs) noexcept;
};

struct mat4 : private equatable<mat4>,
              private multipliable<mat4> {
  float m[16] = {};

  constexpr mat4() noexcept = default;

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

  constexpr auto operator*=(const mat4 &rhs) noexcept;
};

constexpr mat4 transpose(const mat4 &m) noexcept;
constexpr mat4 inverse(const mat4 &m) noexcept;

constexpr mat4 make_identity() noexcept;

constexpr mat4 make_translate(const vec3 &v) noexcept;
constexpr mat4 make_rotation(const vec3 &v) noexcept;
constexpr mat4 make_scale(const vec3 &v) noexcept;

constexpr mat4 make_lookat(const vec3 &from, const vec3 &to,
                           const vec3 &up) noexcept;

constexpr mat4 make_perspective() noexcept;
constexpr mat4 make_orthographic() noexcept;

struct quat : equatable<quat>, multipliable<quat> {
  float r = 0;
  vec3 v{};

  constexpr quat() noexcept = default;
  constexpr quat(float r, vec3 v) noexcept : r(r), v(v){};

  constexpr auto operator!=(const quat &rhs) const noexcept;
  constexpr auto operator*=(const quat &rhs) noexcept;
};

int main() {}
