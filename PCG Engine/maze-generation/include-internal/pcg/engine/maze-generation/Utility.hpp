#ifndef PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP
#define PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    /// @brief Loops over grid and invoke callback on each node
    /// @param grid Grid representing maze
    /// @param callback User defined callback
    void invokeCallback(const Grid& grid, const MazeCallback& callback);
}

#endif // PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP
