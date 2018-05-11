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

constexpr float squared_length(const vec3& vec) {
  return dot(vec, vec);
}
constexpr float length(const vec3& vec) {
  return std::sqrt(squared_length(vec));
}
constexpr float normalize(const vec3& vec) {
  return vec / length(vec);
}
constexpr float dot(const vec3& lhs, const vec3& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
constexpr vec3 cross(const vec3& lhs, const vec3& rhs) {
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
