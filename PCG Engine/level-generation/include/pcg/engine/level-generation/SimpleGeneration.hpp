#ifndef PCG_ENGINE_LEVEL_GENERATION_SIMPLE_GENERATION_HPP
#define PCG_ENGINE_LEVEL_GENERATION_SIMPLE_GENERATION_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>

namespace pcg::engine::level_generation
{
    void simpleGeneration(GenerationData* data, math::Axis axis, math::Direction direction, utility::CallbackFunctor<math::Vector3>&& callback);
}

#endif // PCG_ENGINE_LEVEL_GENERATION_SIMPLE_GENERATION_HPP
