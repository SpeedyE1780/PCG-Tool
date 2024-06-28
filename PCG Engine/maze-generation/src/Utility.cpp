#include <pcg/engine/maze-generation/Utility.hpp>

namespace pcg::engine::maze_generation
{
    void invokeNodeCallback(int x, int y, const Grid& grid, const MazeCallback& callback)
    {
        callback(x, y, grid[y][x]);
    }

    void invokeNodePairCallback(int x, int y, int adjacentX, int adjacentY, const Grid& grid, const MazeCallback& callback)
    {
        invokeNodeCallback(x, y, grid, callback);
        invokeNodeCallback(adjacentX, adjacentY, grid, callback);
    }

    void invokeCallback(const Grid& grid, const MazeCallback& callback)
    {
        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = 0; x < grid[0].size(); ++x)
            {
                invokeNodeCallback(x, y, grid, callback);
            }
        }
    }
}
