#include <pcg/engine/maze/Wilson.hpp>

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
            utility::enums::Direction direction;
        };

        std::vector<WilsonWalkData> walk(const Grid& grid, std::vector<utility::enums::Direction>& directions, std::default_random_engine& randomEngine)
        {
            const int width = grid.size();
            const int height = grid[0].size();
            int x = 0;
            int y = 0;

            do
            {
                x = randomEngine() % width;
                y = randomEngine() % height;
            } while (grid[y][x] != utility::enums::Direction::none);

            int startX = x;
            int startY = y;
            bool walking = true;

            std::map<std::tuple<int, int>, utility::enums::Direction> visits;
            visits[{x, y}] = utility::enums::Direction::none;

            while (walking)
            {
                walking = false;
                std::shuffle(begin(directions), end(directions), randomEngine);

                for (utility::enums::Direction direction : directions)
                {
                    auto [nx, ny] = getNeighborXY(x, y, direction);

                    if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                    {
                        visits[{x, y}] = direction;

                        if (grid[ny][nx] != utility::enums::Direction::none)
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
                utility::enums::Direction direction = visits[{x, y}];
                oss << "Adding: " << x << "-" << y << " to path";
                utility::logInfo(oss.str());

                path.emplace_back(WilsonWalkData{ x, y, direction });
                std::tie(x, y) = getNeighborXY(x, y, direction);
            }

            return path;
        }
    }

    void wilson(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        utility::logInfo("Wilson Maze Generation Started");

        std::ostringstream oss{};
        std::vector<utility::enums::Direction> directions{ utility::enums::Direction::left, utility::enums::Direction::right, utility::enums::Direction::forward, utility::enums::Direction::backward };
        auto randomDevice = std::random_device{};
        auto randomEngine = std::default_random_engine{ randomDevice() };

        Grid grid = generateGrid(width, height);
        int x = randomEngine() % width;
        int y = randomEngine() % height;
        int unvisited = width * height - 1;

        grid[y][x] = static_cast<utility::enums::Direction>(in);

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
                unvisited -= 1;

                if (!invokeAfterGeneration)
                {
                    callback(x, y, grid[y][x]);
                    callback(nx, ny, grid[ny][nx]);
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

        utility::logInfo("Wilson Maze Generation Ended");
    }
}
