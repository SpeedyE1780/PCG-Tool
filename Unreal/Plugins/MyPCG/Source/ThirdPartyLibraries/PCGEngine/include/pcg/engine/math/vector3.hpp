#ifndef PCG_ENGINE_MATH_VECTOR3_HPP
#define PCG_ENGINE_MATH_VECTOR3_HPP

#include <cstddef>

namespace pcg::engine::math
{
    struct Vector3
    {
        void operator+=(const Vector3& rhs);

        static const Vector3 right;
        static const Vector3 left;
        static const Vector3 up;
        static const Vector3 down;
        static const Vector3 forward;
        static const Vector3 backward;

        float x;
        float y;
        float z;
    };

    struct Vector3Hash
    {
        std::size_t operator()(const math::Vector3& vector) const noexcept;
    };

    Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    bool operator==(const Vector3& lhs, const Vector3& rhs);
    Vector3 operator*(const Vector3& vector, float scalar);
}

#endif // PCG_ENGINE_MATH_VECTOR3_HPP
