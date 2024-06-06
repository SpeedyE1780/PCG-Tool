#include <pcg/engine/math/vector3.hpp>

#include <unordered_set>

namespace pcg::engine::math
{
    const Vector3 Vector3::right{ 1, 0, 0 };
    const Vector3 Vector3::left{ -1, 0, 0 };
    const Vector3 Vector3::up{ 0, 1, 0 };
    const Vector3 Vector3::down{ 0, -1, 0 };
    const Vector3 Vector3::forward{ 0, 0 ,1 };
    const Vector3 Vector3::backward{ 0, 0, -1 };

    void Vector3::operator+=(const Vector3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
    }

    std::size_t Vector3Hash::operator()(const Vector3& vector) const noexcept
    {
        std::size_t x = std::hash<float>{}(vector.x);
        std::size_t y = std::hash<float>{}(vector.y);
        std::size_t z = std::hash<float>{}(vector.z);

        return x ^ (y << 1) ^ (z << 2);
    }

    Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
    {
        Vector3 result{};
        result.x = lhs.x + rhs.x;
        result.y = lhs.y + rhs.y;
        result.z = lhs.z + rhs.z;
        return result;
    }

    bool operator==(const Vector3& lhs, const Vector3& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }

    Vector3 operator*(const Vector3& vector, float scalar)
    {
        Vector3 scaledVector = vector;
        scaledVector.x *= scalar;
        scaledVector.y *= scalar;
        scaledVector.z *= scalar;
        return scaledVector;
    }
}
