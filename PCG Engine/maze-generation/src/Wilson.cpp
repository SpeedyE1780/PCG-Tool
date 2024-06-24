#include <pcg/engine/maze-generation/Wilson.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <map>
#include <random>
#include <sstream>
#include <tuple>
#include <vector>

namespace pcg::engine::maze_generation
{
    namespace
    {
        /// @brief POD class containing info of nodes saved during wilson walk
        struct WilsonWalkData
        {
            int x;
            int y;
            utility::enums::Direction direction;
        };

        /// @brief Find a node that belongs to the maze
        /// @param grid Maze grid representation
        /// @param width Grid width
        /// @param height Grid height
        /// @param randomEngine Random number generator used for shuffling
        /// @return 
        std::tuple<int, int> findStartingNode(const Grid& grid, int width, int height, std::default_random_engine& randomEngine)
        {
            int x = 0;
            int y = 0;

            do
            {
                x = randomEngine() % width;
                y = randomEngine() % height;
            } while (grid[y][x] != utility::enums::Direction::none);

            return { x, y };
        }

        /// @brief Get path used to reach node in maze
        /// @param startX Starting x coordinate where walk started
        /// @param startY Starting y coordinate where walk started
        /// @param visits Map containing all nodes visited during walk
        /// @return A path from starting node to node in maze
        std::vector<WilsonWalkData> getPath(int startX, int startY, const std::map<std::tuple<int, int>, utility::enums::Direction>& visits)
        {
            std::vector<WilsonWalkData> path{};

            int x = startX;
            int y = startY;

            while (visits.find({ x, y }) != visits.end())
            {
                std::ostringstream oss{};
                utility::enums::Direction direction = visits.at({ x, y });
                oss << "Adding: " << x << "-" << y << " to path";
                utility::logInfo(oss.str());
                path.emplace_back(WilsonWalkData{ x, y, direction });
                std::tie(x, y) = getAdjacentCoordinates(x, y, direction);
            }

            return path;
        }

        /// @brief Walk in maze until a node belonging to the maze is reached
        /// @param grid Maze grid representation
        /// @param directions Vector of valid directions
        /// @param randomEngine Random number generator used for shuffling
        /// @return A vector of nodes that should be added to the grid
        std::vector<WilsonWalkData> walk(const Grid& grid, std::vector<utility::enums::Direction>& directions, std::default_random_engine& randomEngine)
        {
            const int height = grid.size();
            const int width = grid[0].size();
            auto [x, y] = findStartingNode(grid, width, height, randomEngine);
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
                    auto [nx, ny] = getAdjacentCoordinates(x, y, direction);

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

            return getPath(startX, startY, visits);
        }
    }

    void wilson(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        utility::logInfo("Wilson Maze Generation Started");

        std::ostringstream oss{};
        Directions directions = getDefaultDirections();
        auto randomEngine = std::default_random_engine{ math::Random::seed };

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
                auto [nx, ny] = getAdjacentCoordinates(x, y, walkData.direction);
                grid[y][x] |= walkData.direction;
                grid[ny][nx] |= utility::enums::getFlippedDirection(walkData.direction);
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
