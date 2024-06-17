#ifndef PCG_ENGINE_MAZE_BINARY_TREE_HPP
#define PCG_ENGINE_MAZE_BINARY_TREE_HPP

#include <pcg/engine/maze/Common.hpp>

namespace pcg::engine::maze
{
    enum class Diagonal
    {
        NE,
        NW,
        SE,
        SW
    };

    void binaryTree(int width, int height, Diagonal diagonal, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_BINARY_TREE_HPP
