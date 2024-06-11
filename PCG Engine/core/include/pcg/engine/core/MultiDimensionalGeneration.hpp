#ifndef PCG_ENGINE_CORE_MULTI_DIMENSIONAL_GENERATION_HPP
#define PCG_ENGINE_CORE_MULTI_DIMENSIONAL_GENERATION_HPP

#include <pcg/engine/core/GenerationData.hpp>

#include <vector>

namespace pcg::engine::core
{
    void multiDimensionalGeneration(GenerationData* data, const std::vector<const math::Vector3*>& directions, bool disableOverlap, addPointCallback callback);
}

#endif // PCG_ENGINE_CORE_MULTI_DIMENSIONAL_GENERATION_HPP
