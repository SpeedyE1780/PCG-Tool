#ifndef PCG_ENGINE_LEVEL_GENERATION_WAVE_FUNCTION_COLLAPSE_HPP
#define PCG_ENGINE_LEVEL_GENERATION_WAVE_FUNCTION_COLLAPSE_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>
#include <pcg/engine/utility/Enums.hpp>

#include <pcg/engine/math/vector3.hpp>

namespace pcg::engine::level_generation
{
    /// @brief Generate a level using the Wave Function Collapse Algorithm
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param mode If Breadth-First Search (BFS) or Depth-First Search (DFS) should be used
    /// @param axes Axes flag indicating which axes are being used
    /// @param callback Callback when a node is generated
    void waveFunctionCollapse(const GenerationData& data, ExpansionMode mode, math::Axis axes, utility::CallbackFunctor<void(math::Vector3, utility::enums::Direction)>&& callback);
    /// @brief Generate a grid using the Wave Function Collapse Algorithm
    /// @param width Grid width
    /// @param height Grid height
    /// @param callback Callback when a node is generated
    void waveFunctionCollapse(int width, int height, utility::CallbackFunctor<void(int, int, utility::enums::Direction)>&& callback);
}

#endif // PCG_ENGINE_LEVEL_GENERATION_WAVE_FUNCTION_COLLAPSE_HPP
