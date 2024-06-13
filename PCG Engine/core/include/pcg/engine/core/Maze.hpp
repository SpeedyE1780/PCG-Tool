#ifndef PCG_ENGINE_CORE_MAZE_HPP
#define PCG_ENGINE_CORE_MAZE_HPP

namespace pcg::engine::core
{
    typedef void (*addMazePointCallback)(int x, int y, int neighbors);

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
