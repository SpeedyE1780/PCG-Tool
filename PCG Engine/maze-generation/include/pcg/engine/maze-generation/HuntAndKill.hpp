#ifndef PCG_ENGINE_MAZE_GENERATION_HUNT_AND_KILL_HPP
#define PCG_ENGINE_MAZE_GENERATION_HUNT_AND_KILL_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    void huntAndKill(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_GENERATION_HUNT_AND_KILL_HPP
