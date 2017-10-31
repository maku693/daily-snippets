#include <cmath>

struct vec3 {
  float x;
  float y;
  float z;

  constexpr vec3& operator/=(float rhs) noexcept {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

  constexpr vec3& operator/(float rhs) noexcept {
    return *this /= rhs;
  }
};

constexpr float squared_length(vec3& vec) {
  return dot(vec, vec);
}
constexpr float length(vec3& vec) {
  return std::sqrt(squared_length(vec));
}
constexpr vec3 normalize(vec3& vec) {
  return vec / length(vec);
}
constexpr float dot(vec3& lhs, vec3& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
constexpr vec3 cross(vec3& lhs, vec3& rhs) {
  return vec3 {
    lhs.y * rhs.z - lhs.z * rhs.y,
    lhs.z * rhs.x - lhs.x * rhs.z,
    lhs.x * rhs.y - lhs.y * rhs.x
  };
}

#include <iostream>

int main() {
  return 0;
}
