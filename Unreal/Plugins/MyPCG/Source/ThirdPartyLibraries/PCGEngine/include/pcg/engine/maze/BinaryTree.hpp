#ifndef PCG_ENGINE_MAZE_BINARY_TREE_HPP
#define PCG_ENGINE_MAZE_BINARY_TREE_HPP

#include <pcg/engine/maze/Common.hpp>
#include <pcg/engine/maze/Enums.hpp>

namespace pcg::engine::maze
{
    void binaryTree(int width, int height, Diagonal diagonal, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_BINARY_TREE_HPP
