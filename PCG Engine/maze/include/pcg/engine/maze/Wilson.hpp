#ifndef PCG_ENGINE_MAZE_WILSON_HPP
#define PCG_ENGINE_MAZE_WILSON_HPP

#include <pcg/engine/maze/Common.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <map>
#include <random>
#include <sstream>
#include <tuple>
#include <vector>

namespace pcg::engine::maze
{
    namespace
    {
        struct WilsonWalkData
        {
            int x;
            int y;
            int direction;
        };

        std::vector<WilsonWalkData> walk(const std::vector<std::vector<int>>& grid, std::vector<int>& directions, std::default_random_engine& randomEngine)
        {
            const int width = grid.size();
            const int height = grid[0].size();
            int x = 0;
            int y = 0;

            do
            {
                x = randomEngine() % width;
                y = randomEngine() % height;
            } while (grid[y][x] != 0);

            int startX = x;
            int startY = y;
            bool walking = true;

            std::map<std::tuple<int, int>, int> visits;
            visits[{x, y}] = 0;

            while (walking)
            {
                walking = false;
                std::shuffle(begin(directions), end(directions), randomEngine);

                for (int direction : directions)
                {
                    auto [nx, ny] = getNeighborXY(x, y, direction);

                    if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                    {
                        visits[{x, y}] = direction;

                        if (grid[ny][nx] != 0)
                        {
                            break;
                        }
                        else
                        {
                            x = nx;
                            y = ny;
                            walking = true;
                            break;
                        }
                    }
                }
            }

            std::vector<WilsonWalkData> path{};

            x = startX;
            y = startY;

            while (visits.find({ x, y }) != visits.end())
            {
                std::ostringstream oss{};
                int direction = visits[{x, y}];
                oss << "Adding: " << x << "-" << y << ": " << direction << " to path";
                utility::logInfo(oss.str());

                path.emplace_back(WilsonWalkData{ x, y, direction });
                std::tie(x, y) = getNeighborXY(x, y, direction);
            }

            return path;
        }
    }

    template<typename addMazePointCallback>
    void wilson(int width, int height, addMazePointCallback callback)
    {
        utility::logInfo("Wilson Maze Generation Started");

        std::ostringstream oss{};
        std::vector<int> directions{ left, right, up, down };
        auto randomDevice = std::random_device{};
        auto randomEngine = std::default_random_engine{ randomDevice() };

        std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));
        int x = randomEngine() % width;
        int y = randomEngine() % height;
        int unvisited = width * height - 1;

        grid[y][x] = in;

        oss << "Started with:" << x << "-" << y << " unvisited: " << unvisited;
        utility::logInfo(oss.str());
        oss.str("");

        while (unvisited > 0)
        {
            for (const auto& walkData : walk(grid, directions, randomEngine))
            {
                int x = walkData.x;
                int y = walkData.y;
                auto [nx, ny] = getNeighborXY(x, y, walkData.direction);
                grid[y][x] |= walkData.direction;
                grid[ny][nx] |= getFlippedDirection(walkData.direction);
                oss << "Value set at " << x << "-" << y << "/" << nx << "-" << ny << " unvisited: " << unvisited;
                utility::logInfo(oss.str());
                oss.str("");
                callback(x, y, grid[y][x]);
                callback(nx, ny, grid[ny][nx]);
                unvisited -= 1;
            }
        }

        utility::logInfo("Wilson Maze Generation Ended");
    }
}

#endif // PCG_ENGINE_MAZE_WILSON_HPP
