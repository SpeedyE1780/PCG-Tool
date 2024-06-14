#ifndef PCG_ENGINE_CORE_MAZE_HPP
#define PCG_ENGINE_CORE_MAZE_HPP

namespace pcg::engine::core
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

    void aldousBroder(int width, int height, addMazePointCallback callback);
    void wilson(int width, int height, addMazePointCallback callback);
    void binaryTree(int width, int height, Diagonal diagonal, addMazePointCallback callback);
    void sidewinder(int width, int height, addMazePointCallback callback);
}

#endif // PCG_ENGINE_CORE_MAZE_HPP
