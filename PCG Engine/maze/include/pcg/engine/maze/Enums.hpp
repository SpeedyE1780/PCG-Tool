#ifndef PCG_ENGINE_MAZE_ENUMS_HPP
#define PCG_ENGINE_MAZE_ENUMS_HPP

namespace pcg::engine::maze
{
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
}

#endif // PCG_ENGINE_MAZE_ENUMS_HPP
