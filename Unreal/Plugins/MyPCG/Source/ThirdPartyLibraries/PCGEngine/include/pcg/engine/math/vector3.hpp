#ifndef PCG_ENGINE_MATH_VECTOR3_HPP
#define PCG_ENGINE_MATH_VECTOR3_HPP

#include <pcg/engine/math/enums.hpp>

#include <pcg/engine/utility/Enums.hpp>

#include <cstddef>
#include <vector>

namespace pcg::engine::math
{
    /// @brief Class representing a Vector in 3D space
    struct Vector3
    {
        Vector3& operator+=(const Vector3& rhs);

        static const Vector3 zero;
        static const Vector3 right;
        static const Vector3 left;
        static const Vector3 up;
        static const Vector3 down;
        static const Vector3 forward;
        static const Vector3 backward;

        double x = 0;
        double y = 0;
        double z = 0;

        /// @brief Get vector containing unit vectors of given axes
        /// @param axes Bit flag representing enabled axes
        /// @return Vector containing unit vectors of enabled axes
        static std::vector<const Vector3*> getUnitVectors(Axis axes);

        /// @brief Get a unit vector from a direction
        /// @param direction Direction who's unit vector we need
        /// @return The vector corresponding to the given direction
        static const math::Vector3& getUnitVectorFromDirection(utility::enums::Direction direction);
    };

    Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    bool operator==(const Vector3& lhs, const Vector3& rhs);
    Vector3 operator*(const Vector3& vector, double scalar);
}

namespace std
{
    /// @brief Specialization of std::hash with Vector3 class
    template <>
    struct hash<pcg::engine::math::Vector3>
    {
        size_t operator()(const pcg::engine::math::Vector3& vector) const
        {
            std::size_t x = std::hash<double>{}(vector.x);
            std::size_t y = std::hash<double>{}(vector.y);
            std::size_t z = std::hash<double>{}(vector.z);

            return x ^ (y << 1) ^ (z << 2);
        }
    };
}

#endif // PCG_ENGINE_MATH_VECTOR3_HPP
