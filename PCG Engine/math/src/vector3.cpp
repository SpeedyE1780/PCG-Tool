#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/logging.hpp>
#include <pcg/engine/utility/Enums.hpp>

#include <unordered_set>

namespace pcg::engine::math
{
    const Vector3 Vector3::zero{ 0, 0, 0 };
    const Vector3 Vector3::right{ 1, 0, 0 };
    const Vector3 Vector3::left{ -1, 0, 0 };
    const Vector3 Vector3::up{ 0, 1, 0 };
    const Vector3 Vector3::down{ 0, -1, 0 };
    const Vector3 Vector3::forward{ 0, 0, 1 };
    const Vector3 Vector3::backward{ 0, 0, -1 };

    Vector3& Vector3::operator+=(const Vector3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
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

    Vector3 operator*(const Vector3& vector, double scalar)
    {
        Vector3 scaledVector = vector;
        scaledVector.x *= scalar;
        scaledVector.y *= scalar;
        scaledVector.z *= scalar;
        return scaledVector;
    }

    std::vector<const Vector3*> Vector3::getUnitVectors(Axis axes)
    {
        std::vector<const Vector3*> directions{};

        if (utility::enums::hasFlag(axes, Axis::positiveX))
        {
            directions.emplace_back(&Vector3::right);
        }

        if (utility::enums::hasFlag(axes, Axis::negativeX))
        {
            directions.emplace_back(&Vector3::left);
        }

        if (utility::enums::hasFlag(axes, Axis::positiveY))
        {
            directions.emplace_back(&Vector3::up);
        }

        if (utility::enums::hasFlag(axes, Axis::negativeY))
        {
            directions.emplace_back(&Vector3::down);
        }

        if (utility::enums::hasFlag(axes, Axis::positiveZ))
        {
            directions.emplace_back(&Vector3::forward);
        }

        if (utility::enums::hasFlag(axes, Axis::negativeZ))
        {
            directions.emplace_back(&Vector3::backward);
        }

        if (directions.size() == 0)
        {
            utility::logError("Invalid axis given to getUnitVectors");
        }

        return directions;
    }

    const Vector3& Vector3::getUnitVectorFromDirection(utility::enums::Direction direction)
    {
        switch (direction)
        {
        case utility::enums::Direction::left:
        {
            return Vector3::left;
        }
        case utility::enums::Direction::right:
        {
            return Vector3::right;
        }
        case utility::enums::Direction::up:
        {
            return Vector3::up;
        }
        case utility::enums::Direction::down:
        {
            return Vector3::down;
        }
        case utility::enums::Direction::forward:
        {
            return Vector3::forward;
        }
        case utility::enums::Direction::backward:
        {
            return Vector3::backward;
        }
        case utility::enums::Direction::none:
        default:
        {
            utility::logWarning("None direction passed in to getUnitVectorFromDirection");
            return Vector3::zero;
        }
        }
    }
}
