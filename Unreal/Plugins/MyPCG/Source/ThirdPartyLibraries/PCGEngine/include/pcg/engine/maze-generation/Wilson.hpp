#ifndef PCG_ENGINE_MAZE_GENERATION_WILSON_HPP
#define PCG_ENGINE_MAZE_GENERATION_WILSON_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    /// @brief Geneate maze using Wilson Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param callback Callback when a node is generated
    void wilson(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback);
}

#endif // PCG_ENGINE_MAZE_GENERATION_WILSON_HPP
