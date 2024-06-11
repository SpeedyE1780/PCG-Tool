#include <pcg/engine/core/api.hpp>
#include <pcg/engine/core/SimpleGeneration.hpp>
#include <pcg/engine/core/MultiDimensionalGeneration.hpp>

namespace pcg::engine::core
{
    void setSeed(unsigned int seed)
    {
        math::Random::seed(seed);
    }

    void setRandomGenerator(math::setSeed seed, math::generateNumber generate)
    {
        math::initializeRandom(seed, generate);
    }

    void setLoggingFunction(utility::logMessage logFunction)
    {
        utility::setLoggingFunction(logFunction);
    }

    void generation1D(GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback)
    {
        simpleGeneration(data, axis, direction, callback);
    }

    void generation2D(GenerationData* data, math::Plane plane, bool disableOverlap, addPointCallback callback)
    {
        std::vector<const math::Vector3*> directions = getPlaneUnitVectors(plane);

        if (directions.empty())
        {
            return;
        }

        multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback)
    {
        static const std::vector<const math::Vector3*> directions
        {
            {
                &math::Vector3::right,
                &math::Vector3::left,
                &math::Vector3::up,
                &math::Vector3::down,
                &math::Vector3::forward,
                &math::Vector3::backward
            }
        };

        multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }
}
