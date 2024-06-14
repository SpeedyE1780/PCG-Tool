#include <pcg/engine/maze/AldousBroder.hpp>
#include <pcg/engine/maze/Common.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <random>
#include <sstream>
#include <vector>

namespace pcg::engine::maze
{
    void aldousBroder(int width, int height, MazeCallback&& callback)
    {
        std::ostringstream oss{};

        utility::logInfo("Aldous - Broder Maze Generation Started");

        std::vector<int> directions{ left, right, up, down };
        auto randomDevice = std::random_device{};
        auto randomEngine = std::default_random_engine{ randomDevice() };

        grid grid = generateGrid(width, height);

        int x = randomEngine() % width;
        int y = randomEngine() % height;
        int unvisited = width * height - 1;

        oss << "Started with:" << x << "-" << y << " unvisited: " << unvisited;
        utility::logInfo(oss.str());
        oss.str("");

        while (unvisited > 0)
        {
            std::shuffle(begin(directions), end(directions), randomEngine);

            for (int direction : directions)
            {
                auto [nx, ny] = getNeighborXY(x, y, direction);

                if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                {
                    if (grid[ny][nx] == 0)
                    {
                        grid[y][x] |= direction;
                        grid[ny][nx] |= getFlippedDirection(direction);
                        unvisited -= 1;
                        oss << "Value set at " << x << "-" << y << "/" << nx << "-" << ny << " unvisited: " << unvisited;
                        utility::logInfo(oss.str());
                        oss.str("");
                        callback(x, y, grid[y][x]);
                        callback(nx, ny, grid[ny][nx]);
                    }

                    x = nx;
                    y = ny;
                    break;
                }
            }
        }

        utility::logInfo("Aldous - Broder Maze Generation Ended");
    }
}

