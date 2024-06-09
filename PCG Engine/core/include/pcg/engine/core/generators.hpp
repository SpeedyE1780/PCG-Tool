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

    struct GenerationData
    {
        unsigned int limit;
        float size;
        math::Vector3 startPoint;
    };

    PCG_ENGINE_CORE_API void setSeed(unsigned int seed);
    PCG_ENGINE_CORE_API void setRandomGenerator(math::setSeed seed, math::generateNumber generate);
    PCG_ENGINE_CORE_API void setLoggingFunction(utility::logMessage logFunction);
    PCG_ENGINE_CORE_API void simpleGeneration(GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation2D(GenerationData* data, math::Plane plane, bool disableOverlap, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback);
}

#endif // PCG_ENGINE_CORE_CORE_HPP
