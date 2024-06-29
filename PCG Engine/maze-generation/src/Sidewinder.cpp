#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/Sidewinder.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <sstream>

namespace pcg::engine::maze_generation
{
    namespace
    {
        /// @brief Ends current run of nodes and carve a path north
        /// @param grid Maze grid representation
        /// @param x x coordinate in grid
        /// @param y y coordinate in grid
        /// @param runStart x coordinate where run of node started
        /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
        /// @param callback Callback when a node is generated
        void carveNoth(Grid& grid, std::size_t x, std::size_t y, std::size_t& runStart, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            utility::logInfo("Ending run and carving north");
            int cell = math::Random::generateNumber(runStart, x + 1);
            addAdjacentNodePath(cell, y, cell, y - 1, NodeValue::backward, grid);
            runStart = x + 1;

            if (!invokeAfterGeneration)
            {
                invokeNodePairCallback(cell, y, cell, y - 1, grid, callback);
            }
        }

        /// @brief Expand current run of node and add node to the east
        /// @param grid Maze grid representation
        /// @param x x coordinate in grid
        /// @param y y coordinate in grid
        /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
        /// @param callback Callback when a node is generated
        void carveEast(Grid& grid, std::size_t x, std::size_t y, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            utility::logInfo("Carving east");
            addAdjacentNodePath(x, y, x + 1, y, NodeValue::right, grid);

            if (!invokeAfterGeneration)
            {
                invokeNodePairCallback(x, y, x + 1, y, grid, callback);
            }
        }
    }

    void sidewinder(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        utility::logInfo("Sidewinder Maze Generation Started");

        Grid grid = generateGrid(width, height);

        for (std::size_t h = 0; h < height; ++h)
        {
            std::size_t runStart = 0;

            for (std::size_t w = 0; w < width; ++w)
            {
                if (h > 0 && (w + 1 == width || math::Random::generateNumber(0, 2) == 0))
                {
                    carveNoth(grid, w, h, runStart, invokeAfterGeneration, callback);
                }
                else if (w + 1 < width)
                {
                    carveEast(grid, w, h, invokeAfterGeneration, callback);
                }
            }
        }

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }

        utility::logInfo("Sidewinder Maze Generation Started");
    }
}
