#ifndef PCG_ENGINE_MAZE_GENERATION_GROWING_TREE_HPP
#define PCG_ENGINE_MAZE_GENERATION_GROWING_TREE_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    enum class GrowingTreeSelectionMethod
    {
        oldest = 0,
        middle = 1,
        newest = 2,
        random = 3
    };

    /// @brief Geneate maze using Growing Tree Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param callback Callback when a node is generated
    void growingTree(int width, int height, bool invokeAfterGeneration, GrowingTreeSelectionMethod method, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_GENERATION_GROWING_TREE_HPP
