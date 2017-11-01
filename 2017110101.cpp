#include <cmath>

namespace PathTracer {

namespace Math {

    template <class Vec>
    struct VecFacade {
        constexpr Vec operator/(float rhs) noexcept
        {
            return static_cast<T>(*this) /= rhs;
        }
    };

    struct Vec3 : public VecFacade<Vec3> {
        float x;
        float y;
        float z;

        constexpr Vec3 operator/=(float rhs) noexcept
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }
    };

    constexpr float dot(Vec3 lhs, Vec3 rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    constexpr Vec3 cross(Vec3 lhs, Vec3 rhs)
    {
        return Vec3 {
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }

    constexpr float squared_length(Vec3 v)
    {
        return dot(v, v);
    }

    float length(Vec3 v)
    {
        return std::sqrt(squared_length(v));
    }

    Vec3 normalize(Vec3 v)
    {
        const float len = length(v);
        return Vec3 {
            v.x / len,
            v.y / len,
            v.z / len
        };
    }

} // namespace Math

class Scene {};

class Renderer {};

} // namespace PathTracer

#include <iostream>
#include <memory>

int main()
{
    const auto r = std::make_unique<Renderer>();
    return 0;
}
