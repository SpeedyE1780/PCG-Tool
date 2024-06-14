#ifndef PCG_ENGINE_MAZE_WILSON_HPP
#define PCG_ENGINE_MAZE_WILSON_HPP

#include <pcg/engine/maze/Common.hpp>

namespace pcg::engine::maze
{
    void wilson(int width, int height, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_WILSON_HPP
