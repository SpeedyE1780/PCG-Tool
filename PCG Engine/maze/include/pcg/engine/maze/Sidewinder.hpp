#ifndef PCG_ENGINE_MAZE_SIDEWINDER_HPP
#define PCG_ENGINE_MAZE_SIDEWINDER_HPP

#include <pcg/engine/maze/Common.hpp>

namespace pcg::engine::maze
{
    void sidewinder(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_SIDEWINDER_HPP
