#ifndef PCG_ENGINE_CORE_MAZE_HPP
#define PCG_ENGINE_CORE_MAZE_HPP

namespace pcg::engine::core
{
    typedef void (*addMazePointCallback)(int x, int y, int neighbors);

    void aldousBroder(int width, int height, addMazePointCallback callback);
}

#endif // PCG_ENGINE_CORE_MAZE_HPP
