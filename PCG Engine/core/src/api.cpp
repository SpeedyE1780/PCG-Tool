#include <pcg/engine/core/api.hpp>

#include <pcg/engine/core/SimpleGeneration.hpp>

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
}
