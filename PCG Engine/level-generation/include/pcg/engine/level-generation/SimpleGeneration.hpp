#ifndef PCG_ENGINE_LEVEL_GENERATION_SIMPLE_GENERATION_HPP
#define PCG_ENGINE_LEVEL_GENERATION_SIMPLE_GENERATION_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>

namespace pcg::engine::level_generation
{
    /// @brief Generate a linear level on a single axis
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param axis Axis used during level generation (X, Y or Z)
    /// @param callback Callback when a node is generated
    void simpleGeneration(const GenerationData& data, math::Axis axis, utility::CallbackFunctor<void(math::Vector3)>&& callback);
}

#endif // PCG_ENGINE_LEVEL_GENERATION_SIMPLE_GENERATION_HPP
