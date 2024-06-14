#ifndef PCG_ENGINE_MAZE_MAZE_HPP
#define PCG_ENGINE_MAZE_MAZE_HPP

#include <pcg/engine/maze/AldousBroder.hpp>
#include <pcg/engine/maze/Wilson.hpp>

namespace pcg::engine::maze
{
    typedef void (*addMazePointCallback)(int x, int y, int neighbors);

    enum class MazeAlgorithm
    {
        aldousBroder = 0,
        wilson = 1,
        binaryTreeNE = 2,
        binaryTreeNW = 3,
        binaryTreeSE = 4,
        binaryTreeSW = 5,
        sidewinder = 6
    };

    enum class Diagonal
    {
        NE,
        NW,
        SE,
        SW
    };

    void binaryTree(int width, int height, Diagonal diagonal, addMazePointCallback callback);
    void sidewinder(int width, int height, addMazePointCallback callback);
}

#endif // PCG_ENGINE_MAZE_MAZE_HPP
