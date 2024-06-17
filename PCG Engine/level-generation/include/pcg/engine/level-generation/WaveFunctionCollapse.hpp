#ifndef PCG_ENGINE_LEVEL_GENERATION_WAVE_FUNCTION_COLLAPSE_HPP
#define PCG_ENGINE_LEVEL_GENERATION_WAVE_FUNCTION_COLLAPSE_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>
#include <pcg/engine/utility/Enums.hpp>

#include <pcg/engine/math/vector3.hpp>

namespace pcg::engine::level_generation
{
    void waveFunctionCollapse(GenerationData* data, ExpansionMode mode, math::axis::Flag axis, utility::CallbackFunctor<void(math::Vector3, utility::enums::Direction)>&& callback);
}

#endif // PCG_ENGINE_LEVEL_GENERATION_WAVE_FUNCTION_COLLAPSE_HPP
