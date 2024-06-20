#include <pcg/engine/level-generation/SimpleGeneration.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <functional>

namespace pcg::engine::level_generation
{
    namespace
    {
        /// @brief Get function used to get next node position
        /// @param axis Axis followed to spawn nodes
        /// @return Function used to update the node position to the next one
        std::function<void(math::Vector3& position, float offset)> getUpdatePositionFunction(math::Axis axis)
        {
            switch (axis)
            {
            case math::Axis::positiveX:
            {
                return [](math::Vector3& position, float offset)
                    {
                        position.x += offset;
                    };
            }
            case math::Axis::negativeX:
            {
                return [](math::Vector3& position, float offset)
                    {
                        position.x -= offset;
                    };
            }
            case math::Axis::positiveY:
            {
                return [](math::Vector3& position, float offset)
                    {
                        position.y += offset;
                    };
            }
            case math::Axis::negativeY:
            {
                return [](math::Vector3& position, float offset)
                    {
                        position.y -= offset;
                    };
            }
            case math::Axis::positiveZ:
            {
                return [](math::Vector3& position, float offset)
                    {
                        position.z += offset;
                    };
            }
            case math::Axis::negativeZ:
            {
                return [](math::Vector3& position, float offset)
                    {
                        position.z -= offset;
                    };
            }
            default:
            {
                utility::logError("Invalid axis given to getUpdatePositionFunction");
                return nullptr;
            }
            }
        }
    }

    void simpleGeneration(const GenerationData& data, math::Axis axis, utility::CallbackFunctor<void(math::Vector3)>&& callback)
    {
        utility::logInfo("Simple Generation Started");
        std::function<void(math::Vector3& position, float offset)> updatePosition = getUpdatePositionFunction(axis);
        math::Vector3 position = data.startPoint;

        if (!updatePosition)
        {
            return;
        }

        for (int i = 0; i < data.count; ++i)
        {
            callback(position);
            updatePosition(position, data.size);
        }

        utility::logInfo("Simple Generation Ended");
    }
}
