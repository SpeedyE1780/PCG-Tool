#ifndef PCG_ENGINE_LEVEL_GENERATION_GRID_WAVE_FUNCTION_COLLAPSE_HPP
#define PCG_ENGINE_LEVEL_GENERATION_GRID_WAVE_FUNCTION_COLLAPSE_HPP

#include <pcg/engine/math/enums.hpp>

#include <pcg/engine/utility/Enums.hpp>

#include <functional>

namespace pcg::engine::level_generation
{
    /// @brief Generate a grid using the Wave Function Collapse Algorithm
    /// @param width Grid width
    /// @param height Grid height
    /// @param axes Axes flag indicating which axes are being used
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param callback Callback when a node is generated
    void waveFunctionCollapse(int width, int height, math::Axis axes, bool invokeAfterGeneration, const std::function<void(int, int, utility::enums::Direction)>& callback);
    /// @brief Generate a grid using the Wave Function Collapse Algorithm
    /// @param width Grid width
    /// @param height Grid height
    /// @param depth Grid depth
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param callback Callback when a node is generated
    void waveFunctionCollapse(int width, int height, int depth, bool invokeAfterGeneration, const std::function<void(int, int, int, utility::enums::Direction)>& callback);
}

#endif // PCG_ENGINE_LEVEL_GENERATION_GRID_WAVE_FUNCTION_COLLAPSE_HPP
