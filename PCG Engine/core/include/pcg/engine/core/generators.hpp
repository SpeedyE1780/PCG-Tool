#ifndef PCG_ENGINE_CORE_CORE_HPP
#define PCG_ENGINE_CORE_CORE_HPP

#include <pcg/engine/core/config.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::core
{
    typedef void (*addPointCallback)(math::Vector3 vector);
    typedef void (*addWFCPointCallback)(math::Vector3 vector, int neighbors);

    struct GenerationData
    {
        unsigned int limit;
        float size;
        math::Vector3 startPoint;
    };

    enum Neighbors
    {
        left = 1 << 0,
        right = 1 << 1,
        forward = 1 << 2,
        backward = 1 << 3,
        up = 1 << 4,
        down = 1 << 5
    };

    PCG_ENGINE_CORE_API void setSeed(unsigned int seed);
    PCG_ENGINE_CORE_API void setRandomGenerator(math::setSeed seed, math::generateNumber generate);
    PCG_ENGINE_CORE_API void setLoggingFunction(utility::logMessage logFunction);
    PCG_ENGINE_CORE_API void simpleGeneration(GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation2D(GenerationData* data, math::Plane plane, bool disableOverlap, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback);
    PCG_ENGINE_CORE_API void waveFunctionCollapse(GenerationData* data, addWFCPointCallback callback);
}

#endif // PCG_ENGINE_CORE_CORE_HPP
