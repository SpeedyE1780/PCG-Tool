#include <pcg/engine/core/core.hpp>

#include <functional>
#include <optional>
#include <unordered_set>

namespace pcg::engine::core
{
    static const Vector3 right{ 1, 0, 0 };
    static const Vector3 left{ -1, 0, 0 };
    static const Vector3 up{ 0, 1, 0 };
    static const Vector3 down{ 0, -1, 0 };
    static const Vector3 forward{ 0, 0 ,1 };
    static const Vector3 backward{ 0, 0, -1 };

    int add(int x, int y)
    {
        return x + y;
    }

    void setSeed(unsigned int seed)
    {
        srand(seed);
    }

    void simpleGeneration(GenerationData* data, Axis axis, Direction direction, addPointCallback callback)
    {
        std::function<void()> updatePosition;
        Vector3 position = data->startPoint;
        float offset = direction == Direction::positive ? data->size : -data->size;

        switch (axis)
        {
        case Axis::x:
        {
            updatePosition = [&position, offset]()
                {
                    position.x += offset;
                };
            break;
        }
        case Axis::y:
        {
            updatePosition = [&position, offset]()
                {
                    position.y += offset;
                };
            break;
        }
        case Axis::z:
        {
            updatePosition = [&position, offset]()
                {
                    position.z += offset;
                };
            break;
        }
        default:
        {
            break;
        }
        }

        for (int i = 0; i < data->limit; i++)
        {
            callback(position);
            updatePosition();
        }
    }

    void Vector3::operator+=(const Vector3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
    }

    Vector3 operator*(const Vector3& vector, float scalar)
    {
        Vector3 scaledVector = vector;
        scaledVector.x *= scalar;
        scaledVector.y *= scalar;
        scaledVector.z *= scalar;
        return scaledVector;
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

    struct Vector3Hash
    {
        std::size_t operator()(const Vector3& vector) const noexcept
        {
            std::size_t x = std::hash<float>{}(vector.x);
            std::size_t y = std::hash<float>{}(vector.y);
            std::size_t z = std::hash<float>{}(vector.z);

            return x ^ (y << 1) ^ (z << 2);
        }
    };

    static std::optional<Vector3> getNextPosition(std::unordered_set<Vector3, Vector3Hash>& positions, const Vector3& currentPosition, const std::vector<const Vector3*>& directions, float offset)
    {
        std::vector<Vector3> availablePositions{};

        for (const auto* direction : directions)
        {
            Vector3 position = currentPosition + *direction * offset;

            if (positions.find(position) == end(positions))
            {
                availablePositions.emplace_back(std::move(position));
            }
        }

        if (availablePositions.size() == 0)
        {
            return std::nullopt;
        }

        return availablePositions[rand() % availablePositions.size()];
    }

    static void multiDimensionalGeneration(GenerationData* data, const std::vector<const Vector3*>& directions, bool disableOverlap, addPointCallback callback)
    {
        std::unordered_set<Vector3, Vector3Hash> positions{};
        Vector3 position = data->startPoint;

        for (int i = 0; i < data->limit; i++)
        {
            callback(position);

            if (disableOverlap)
            {
                positions.insert(position);
            }

            auto nextPosition = getNextPosition(positions, position, directions, data->size);

            if (!nextPosition.has_value())
            {
                return;
            }

            position = nextPosition.value();
        }
    }

    void generation2D(GenerationData* data, Plane plane, bool disableOverlap, addPointCallback callback)
    {
        std::vector<const Vector3*> directions{};

        switch (plane)
        {
        case Plane::xy:
            directions.insert(begin(directions), { &right, &left, &up, &down });
            break;
        case Plane::xz:
            directions.insert(begin(directions), { &right, &left, &forward, &backward });
            break;
        case Plane::yz:
            directions.insert(begin(directions), { &up, &down, &forward, &backward });
            break;
        default:
            break;
        }

        multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback)
    {
        static const std::vector<const Vector3*> directions{ {&right, &left, &up, &down, &forward, &backward} };
        multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }
}
