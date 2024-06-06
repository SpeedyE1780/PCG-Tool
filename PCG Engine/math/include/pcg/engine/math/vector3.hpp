#ifndef PCG_ENGINE_MATH_VECTOR3_HPP
#define PCG_ENGINE_MATH_VECTOR3_HPP

namespace pcg::engine::math
{
    struct Vector3
    {
        float x;
        float y;
        float z;

        void operator+=(const Vector3& rhs);
    };

    Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    bool operator==(const Vector3& lhs, const Vector3& rhs);
    Vector3 operator*(const Vector3& vector, float scalar);
}

#endif // PCG_ENGINE_MATH_VECTOR3_HPP
