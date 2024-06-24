#include <pcg/engine/maze-generation/AldousBroder.hpp>
#include <pcg/engine/maze-generation/Common.hpp>

#include <pcg/engine/math/random.hpp>

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

        int x = randomEngine() % width;
        int y = randomEngine() % height;
        int unvisited = width * height - 1;

        oss << "Started with:" << x << "-" << y << " unvisited: " << unvisited;
        utility::logInfo(oss.str());
        oss.str("");

        while (unvisited > 0)
        {
            std::shuffle(begin(directions), end(directions), randomEngine);

            for (utility::enums::Direction direction : directions)
            {
                auto [nx, ny] = getAdjacentCoordinates(x, y, direction);

                if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                {
                    if (grid[ny][nx] == utility::enums::Direction::none)
                    {
                        grid[y][x] |= direction;
                        grid[ny][nx] |= utility::enums::getFlippedDirection(direction);
                        unvisited -= 1;
                        oss << "Value set at " << x << "-" << y << "/" << nx << "-" << ny << " unvisited: " << unvisited;
                        utility::logInfo(oss.str());
                        oss.str("");

                        if (!invokeAfterGeneration)
                        {
                            callback(x, y, grid[y][x]);
                            callback(nx, ny, grid[ny][nx]);
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
            for (int y = 0; y < grid.size(); ++y)
            {
                for (int x = 0; x < grid[0].size(); ++x)
                {
                    callback(x, y, grid[y][x]);
                }
            }
        }

        utility::logInfo("Aldous - Broder Maze Generation Ended");
    }
}

