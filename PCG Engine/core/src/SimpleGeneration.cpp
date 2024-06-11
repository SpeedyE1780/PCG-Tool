#include <pcg/engine/core/SimpleGeneration.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <functional>

namespace pcg::engine::core
{
    void simpleGeneration(GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback)
    {
        utility::logInfo("Simple Generation Started");
        std::function<void()> updatePosition;
        math::Vector3 position = data->startPoint;
        const float offset = direction == math::Direction::positive ? data->size : -data->size;

        switch (axis)
        {
        case math::Axis::x:
        {
            updatePosition = [&position, offset]()
                {
                    position.x += offset;
                };
            break;
        }
        case math::Axis::y:
        {
            updatePosition = [&position, offset]()
                {
                    position.y += offset;
                };
            break;
        }
        case math::Axis::z:
        {
            updatePosition = [&position, offset]()
                {
                    position.z += offset;
                };
            break;
        }
        default:
        {
            utility::logError("Wrong Axis given");
            return;
        }
        }

        for (int i = 0; i < data->limit; ++i)
        {
            callback(position);
            updatePosition();
        }

        utility::logInfo("Simple Generation Ended");
    }
}
