#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>
#include <pcg/engine/maze-generation/Wilson.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <random>
#include <sstream>
#include <tuple>
#include <unordered_map>
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
            NodeValue direction;
        };

        /// @brief Find a node that belongs to the maze
        /// @param grid Maze grid representation
        /// @param width Grid width
        /// @param height Grid height
        /// @param randomEngine Random number generator used for shuffling
        /// @return 
        NodeCoordinates findStartingNode(const Grid& grid, int width, int height, std::default_random_engine& randomEngine)
        {
            while (true)
            {
                NodeCoordinates node = getRandomStartingNode(width, height);

                if (grid[node.y][node.x] == NodeValue::none)
                {
                    return node;
                }
            }
        }

        /// @brief Get path used to reach node in maze
        /// @param startX Starting x coordinate where walk started
        /// @param startY Starting y coordinate where walk started
        /// @param visits Map containing all nodes visited during walk
        /// @return A path from starting node to node in maze
        std::vector<WilsonWalkData> getPath(int startX, int startY, const std::unordered_map<NodeCoordinates, NodeValue>& visits)
        {
            std::vector<WilsonWalkData> path{};

            int x = startX;
            int y = startY;

            while (visits.find(NodeCoordinates{ x, y }) != visits.end())
            {
                std::ostringstream oss{};
                NodeValue direction = visits.at({ x, y });
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
        std::vector<WilsonWalkData> walk(const Grid& grid, std::vector<NodeValue>& directions, std::default_random_engine& randomEngine)
        {
            const int height = grid.size();
            const int width = grid[0].size();
            auto [x, y] = findStartingNode(grid, width, height, randomEngine);
            int startX = x;
            int startY = y;
            bool walking = true;

            std::unordered_map<NodeCoordinates, NodeValue> visits;
            visits[{x, y}] = NodeValue::none;

            while (walking)
            {
                walking = false;
                std::shuffle(begin(directions), end(directions), randomEngine);

                for (NodeValue direction : directions)
                {
                    if (auto [nx, ny] = getAdjacentCoordinates(x, y, direction); isWithinGridBounds(nx, ny, width, height))
                    {
                        visits[{x, y}] = direction;

                        if (grid[ny][nx] != NodeValue::none)
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
        std::default_random_engine randomEngine = math::Random::getDefaultEngine();

        Grid grid = generateGrid(width, height);
        auto [x, y] = getRandomStartingNode(width, height);
        int unvisited = width * height - 1;

        grid[y][x] = NodeValue::in;

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
                addAdjacentNodePath(x, y, nx, ny, walkData.direction, grid);
                unvisited -= 1;
                oss << " unvisited: " << unvisited;
                utility::logInfo(oss.str());
                oss.str("");

                if (!invokeAfterGeneration)
                {
                    invokeNodePairCallback(x, y, nx, ny, grid, callback);
                }
            }
        }

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }

        utility::logInfo("Wilson Maze Generation Ended");
    }
}
