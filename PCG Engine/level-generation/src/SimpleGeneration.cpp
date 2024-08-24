#include <pcg/engine/level-generation/SimpleGeneration.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <functional>

namespace pcg::engine::level_generation
{
    void simpleGeneration(const GenerationData& data, const math::Vector3& offset, utility::CallbackFunctor<void(math::Vector3)>&& callback)
    {
        utility::logInfo("Simple Generation Started");
        math::Vector3 position = data.startPoint;

        for (int i = 0; i < data.count; ++i)
        {
            callback(position);
            position += offset * data.size;
        }

        utility::logInfo("Simple Generation Ended");
    }
}
