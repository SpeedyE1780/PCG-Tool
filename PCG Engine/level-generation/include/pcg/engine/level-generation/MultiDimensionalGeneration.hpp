#ifndef PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP
#define PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/math/enums.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>

#include <vector>

namespace pcg::engine::level_generation
{
    void multiDimensionalGeneration(GenerationData* data, const std::vector<const math::Vector3*>& directions, bool disableOverlap, utility::CallbackFunctor<void(math::Vector3)>&& callback);
}

#endif // PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP
