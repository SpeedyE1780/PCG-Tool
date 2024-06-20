#ifndef PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP
#define PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>

#include <vector>

namespace pcg::engine::level_generation
{
    /// @brief Generate a level on multiple axes
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param directions Directions used  to look for adjacent nodes
    /// @param disableOverlap If true nodes cannot be generated on top of one another
    /// @param callback Callback when a node is generated
    void multiDimensionalGeneration(const GenerationData& data, const std::vector<const math::Vector3*>& directions, bool disableOverlap, utility::CallbackFunctor<void(math::Vector3)>&& callback);
}

#endif // PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP
