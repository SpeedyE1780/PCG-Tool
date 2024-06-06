#include <pcg/engine/core/core.hpp>

#include <functional>

namespace pcg::engine::core
{
    int add(int x, int y)
    {
        return x + y;
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

    void generation2D(GenerationData* data, addPointCallback callback)
    {
        static const Vector3 right{ 1, 0, 0 };
        static const Vector3 left{ -1, 0, 0 };
        static const Vector3 forward{ 0, 0 ,1 };
        static const Vector3 backward{ 0, 0, -1 };

        std::vector<const Vector3*> directions{ { &right, &left, &forward, &backward } };

        Vector3 position = data->startPoint;

        for (int i = 0; i < data->limit; i++)
        {
            callback(position);
            const auto* nextDirection = directions[rand() % directions.size()];
            position += *nextDirection * data->size;
        }
    }
}
