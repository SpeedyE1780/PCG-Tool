#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/AldousBroder.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <random>
#include <sstream>
#include <vector>

namespace pcg::engine::maze_generation
{
    void aldousBroder(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        std::ostringstream oss{};

        utility::logInfo("Aldous - Broder Maze Generation Started");

        Directions directions = getDefaultDirections();
        auto randomEngine = std::default_random_engine{ math::Random::seed };

        Grid grid = generateGrid(width, height);

        auto [x, y] = getRandomStartingNode(width, height);
        int unvisited = width * height - 1;

        oss << "Started with:" << x << "-" << y << " unvisited: " << unvisited;
        utility::logInfo(oss.str());
        oss.str("");

        while (unvisited > 0)
        {
            std::shuffle(begin(directions), end(directions), randomEngine);

            for (NodeValue direction : directions)
            {
                if (auto [nx, ny] = getAdjacentCoordinates(x, y, direction); isWithinGridBounds(nx, ny, width, height))
                {
                    if (grid[ny][nx] == NodeValue::none)
                    {
                        addAdjacentNodePath(x, y, nx, ny, direction, grid);
                        unvisited -= 1;
                        oss << " unvisited: " << unvisited;
                        utility::logInfo(oss.str());
                        oss.str("");

                        if (!invokeAfterGeneration)
                        {
                            invokeNodePairCallback(x, y, nx, ny, grid, callback);
                        }
                    }

                    x = nx;
                    y = ny;
                    break;
                }
            }
        }

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }

        utility::logInfo("Aldous - Broder Maze Generation Ended");
    }
}
