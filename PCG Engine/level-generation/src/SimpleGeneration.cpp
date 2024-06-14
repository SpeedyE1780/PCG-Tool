#include <pcg/engine/level-generation/SimpleGeneration.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <functional>

namespace pcg::engine::level_generation
{
    namespace
    {
        std::function<void(math::Vector3& position, float offset)> getUpdatePositionFunction(math::Axis axis)
        {
            switch (axis)
            {
            case math::Axis::x:
            {
                return [](math::Vector3& position, float offset)
                    {
                        position.x += offset;
                    };
            }
            case math::Axis::y:
            {
                return [](math::Vector3& position, float offset)
                    {
                        position.y += offset;
                    };
            }
            case math::Axis::z:
            {
                return [](math::Vector3& position, float offset)
                    {
                        position.z += offset;
                    };
            }
            default:
            {
                utility::logError("Can't interpret axis returning with no generation");
                return nullptr;
            }
            }
        }
    }

    void simpleGeneration(GenerationData* data, math::Axis axis, math::Direction direction, utility::CallbackFunctor<math::Vector3>&& callback)
    {
        utility::logInfo("Simple Generation Started");
        std::function<void(math::Vector3& position, float offset)> updatePosition = getUpdatePositionFunction(axis);
        math::Vector3 position = data->startPoint;
        const float offset = direction == math::Direction::positive ? data->size : -data->size;

        if (!updatePosition)
        {
            return;
        }

        for (int i = 0; i < data->limit; ++i)
        {
            callback(position);
            updatePosition(position, offset);
        }

        utility::logInfo("Simple Generation Ended");
    }
}
