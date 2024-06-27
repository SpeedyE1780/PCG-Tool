#include <pcg/engine/maze-generation/Utility.hpp>

namespace pcg::engine::maze_generation
{
    void invokeCallback(const Grid& grid, const MazeCallback& callback)
    {
        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = 0; x < grid[0].size(); ++x)
            {
                callback(x, y, grid[y][x]);
            }
        }
    }
}
