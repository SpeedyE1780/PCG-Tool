#ifndef PCG_ENGINE_CORE_API_HPP
#define PCG_ENGINE_CORE_API_HPP

#include <pcg/engine/core/config.hpp>
#include <pcg/engine/core/GenerationData.hpp>
#include <pcg/engine/core/generators.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::core
{
    PCG_ENGINE_CORE_API void setSeed(unsigned int seed);
    PCG_ENGINE_CORE_API void setRandomGenerator(math::setSeed seed, math::generateNumber generate);
    PCG_ENGINE_CORE_API void setLoggingFunction(utility::logMessage logFunction);
    PCG_ENGINE_CORE_API void generation1D(GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation2D(GenerationData* data, math::Plane plane, bool disableOverlap, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback);
    PCG_ENGINE_CORE_API void waveFunctionCollapse(GenerationData* data, ExpansionMode mode, addWFCPointCallback callback);
}

#endif // PCG_ENGINE_CORE_API_HPP
