#ifndef PCG_ENGINE_LEVEL_GENERATION_WAVE_FUNCTION_COLLAPSE_HPP
#define PCG_ENGINE_LEVEL_GENERATION_WAVE_FUNCTION_COLLAPSE_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>

#include <pcg/engine/math/vector3.hpp>

namespace pcg::engine::level_generation
{
    void waveFunctionCollapse(GenerationData* data, ExpansionMode mode, utility::CallbackFunctor<void(math::Vector3, int)>&& callback);
}

#endif // PCG_ENGINE_LEVEL_GENERATION_WAVE_FUNCTION_COLLAPSE_HPP
