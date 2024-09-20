#ifndef PCG_ENGINE_MATH_VECTOR4_HPP
#define PCG_ENGINE_MATH_VECTOR4_HPP

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/Enums.hpp>

#include <cstddef>
#include <vector>

namespace pcg::engine::math
{
    /// @brief Class representing a Vector in 3D space
    struct Vector4
    {
        Vector4() = default;
        ~Vector4() = default;
        Vector4(const Vector4& other) = default;
        Vector4(Vector4&& other) = default;
        Vector4& operator=(const Vector4& rhs) = default;
        Vector4& operator=(Vector4&& rhs) = default;

        Vector4(int x, int y, int z, int w);
        Vector4(const Vector3& vector);

        Vector4& operator+=(const Vector4& rhs);

        static const Vector4 zero;
        static const Vector4 right;
        static const Vector4 left;
        static const Vector4 up;
        static const Vector4 down;
        static const Vector4 forward;
        static const Vector4 backward;
        static const Vector4 in;
        static const Vector4 out;

        float x = 0;
        float y = 0;
        float z = 0;
        float w = 0;

        /// @brief Get vector containing unit vectors of given axes
        /// @param axes Bit flag representing enabled axes
        /// @return Vector containing unit vectors of enabled axes
        static std::vector<const Vector4*> getUnitVectors(Axis axes);

        /// @brief Get a unit vector from a direction
        /// @param direction Direction who's unit vector we need
        /// @return The vector corresponding to the given direction
        static const math::Vector4& getUnitVectorFromDirection(utility::enums::Direction direction);
    };

    Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    bool operator==(const Vector4& lhs, const Vector4& rhs);
    Vector4 operator*(const Vector4& vector, float scalar);
}

namespace std
{
    /// @brief Specialization of std::hash with Vector4 class
    template <>
    struct hash<pcg::engine::math::Vector4>
    {
        size_t operator()(const pcg::engine::math::Vector4& vector) const
        {
            std::size_t x = std::hash<float>{}(vector.x);
            std::size_t y = std::hash<float>{}(vector.y);
            std::size_t z = std::hash<float>{}(vector.z);
            std::size_t w = std::hash<float>{}(vector.w);

            return x ^ (y << 1) ^ (z << 2) ^ (w << 3);
        }
    };
}

#endif // PCG_ENGINE_MATH_VECTOR4_HPP
