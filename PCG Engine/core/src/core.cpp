#include <pcg/engine/core/core.hpp>

#include <functional>

namespace pcg::engine::core
{
    int add(int x, int y)
    {
        return x + y;
    }

    void simpleGeneration(GenerationData* data, Axis axis, addPointCallback callback)
    {
        std::function<void()> updatePosition;
        Vector3 position = data->startPoint;
        float offset = data->size;

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
}
