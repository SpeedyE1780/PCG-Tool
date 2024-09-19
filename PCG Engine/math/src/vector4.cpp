#include <pcg/engine/math/vector4.hpp>

#include <pcg/engine/utility/logging.hpp>
#include <pcg/engine/utility/Enums.hpp>

#include <unordered_set>

namespace pcg::engine::math
{
    const Vector4 Vector4::zero{ 0, 0, 0, 0 };
    const Vector4 Vector4::right{ 1, 0, 0, 0 };
    const Vector4 Vector4::left{ -1, 0, 0, 0 };
    const Vector4 Vector4::up{ 0, 1, 0, 0 };
    const Vector4 Vector4::down{ 0, -1, 0, 0 };
    const Vector4 Vector4::forward{ 0, 0, 1, 0 };
    const Vector4 Vector4::backward{ 0, 0, -1, 0 };
    const Vector4 Vector4::in{ 0, 0, 0, -1 };
    const Vector4 Vector4::out{ 0, 0, 0, -1 };

    Vector4& Vector4::operator+=(const Vector4& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;

        return *this;
    }

    Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
    {
        Vector4 result{};
        result.x = lhs.x + rhs.x;
        result.y = lhs.y + rhs.y;
        result.z = lhs.z + rhs.z;
        result.w = lhs.w + rhs.w;
        return result;
    }

    bool operator==(const Vector4& lhs, const Vector4& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
    }

    Vector4 operator*(const Vector4& vector, float scalar)
    {
        Vector4 scaledVector = vector;
        scaledVector.x *= scalar;
        scaledVector.y *= scalar;
        scaledVector.z *= scalar;
        scaledVector.w *= scalar;
        return scaledVector;
    }

    std::vector<const Vector4*> getUnitVectors(Axis axes)
    {
        std::vector<const Vector4*> directions{};

        if (utility::enums::hasFlag(axes, Axis::positiveX))
        {
            directions.emplace_back(&Vector4::right);
        }

        if (utility::enums::hasFlag(axes, Axis::negativeX))
        {
            directions.emplace_back(&Vector4::left);
        }

        if (utility::enums::hasFlag(axes, Axis::positiveY))
        {
            directions.emplace_back(&Vector4::up);
        }

        if (utility::enums::hasFlag(axes, Axis::negativeY))
        {
            directions.emplace_back(&Vector4::down);
        }

        if (utility::enums::hasFlag(axes, Axis::positiveZ))
        {
            directions.emplace_back(&Vector4::forward);
        }

        if (utility::enums::hasFlag(axes, Axis::negativeZ))
        {
            directions.emplace_back(&Vector4::backward);
        }

        if (directions.size() == 0)
        {
            utility::logError("Invalid axis given to getUnitVectors");
        }

        return directions;
    }

    const Vector4& getUnitVectorFromDirection(utility::enums::Direction direction)
    {
        switch (direction)
        {
        case utility::enums::Direction::left:
        {
            return Vector4::left;
        }
        case utility::enums::Direction::right:
        {
            return Vector4::right;
        }
        case utility::enums::Direction::up:
        {
            return Vector4::up;
        }
        case utility::enums::Direction::down:
        {
            return Vector4::down;
        }
        case utility::enums::Direction::forward:
        {
            return Vector4::forward;
        }
        case utility::enums::Direction::backward:
        {
            return Vector4::backward;
        }
        case utility::enums::Direction::none:
        default:
        {
            utility::logWarning("None direction passed in to getUnitVectorFromDirection");
            return Vector4::zero;
        }
        }
    }
}
