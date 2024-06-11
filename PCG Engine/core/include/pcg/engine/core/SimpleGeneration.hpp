#ifndef PCG_ENGINE_CORE_SIMPLE_GENERATION_HPP
#define PCG_ENGINE_CORE_SIMPLE_GENERATION_HPP

#include <pcg/engine/core/GenerationData.hpp>

#include <pcg/engine/math/enums.hpp>

namespace pcg::engine::core
{
    void simpleGeneration(GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback);
}

#endif // PCG_ENGINE_CORE_SIMPLE_GENERATION_HPP
