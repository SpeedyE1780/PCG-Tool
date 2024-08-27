#ifndef PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP
#define PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <functional>
#include <vector>

namespace pcg::engine::level_generation
{
    /// @brief Generate a level on multiple axes
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param axis Axis used to spawn adjacent nodes
    /// @param disableOverlap If true nodes cannot be generated on top of one another
    /// @param callback Callback when a node is generated
    void multiDimensionalGeneration(const GenerationData& data, math::Axis axis, bool disableOverlap, const std::function<void(math::Vector3)>& callback);
}

#endif // PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP
