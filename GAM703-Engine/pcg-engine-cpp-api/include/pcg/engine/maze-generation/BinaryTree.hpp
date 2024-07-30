#ifndef PCG_ENGINE_MAZE_GENERATION_BINARY_TREE_HPP
#define PCG_ENGINE_MAZE_GENERATION_BINARY_TREE_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    /// @brief Diagonal algorithm will follow
    enum class Diagonal
    {
        NE,
        NW,
        SE,
        SW
    };

    /// @brief Geneate maze using Binary Tree Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param diagonal Diagonal along which generation is taking place
    /// @param callback Callback when a node is generated
    void binaryTree(int width, int height, bool invokeAfterGeneration, Diagonal diagonal, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_GENERATION_BINARY_TREE_HPP
