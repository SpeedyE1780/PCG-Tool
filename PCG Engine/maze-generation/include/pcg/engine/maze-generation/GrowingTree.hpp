#ifndef PCG_ENGINE_MAZE_GENERATION_GROWING_TREE_HPP
#define PCG_ENGINE_MAZE_GENERATION_GROWING_TREE_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    /// @brief Geneate maze using Growing Tree Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param callback Callback when a node is generated
    void growingTree(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_GENERATION_GROWING_TREE_HPP
