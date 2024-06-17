#ifndef PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
#define PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP

#include <pcg/engine/maze/Common.hpp>

namespace pcg::engine::maze
{
    void aldousBroder(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
