#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/HuntAndKill.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <optional>
#include <random>

namespace pcg::engine::maze_generation
{
    namespace
    {
        /// @brief Walk in maze until a node belonging to the maze is reached
        /// @param x Starting x coordinate
        /// @param y Starting y coordinate
        /// @param grid Maze grid representation
        /// @param directions Directions to reach adjacent node
        /// @param randomEngine Random number generator used for shuffling
        /// @param callback User defined callback nullptr if callback should be invoked after maze generation
        void walk(int x, int y, Grid& grid, std::vector<NodeValue>& directions, std::default_random_engine& randomEngine, MazeCallback* callback)
        {
            utility::logInfo("Walking Started");

            const int width = grid.size();
            const int height = grid[0].size();
            bool adjacentNodeFound = true;

            while (adjacentNodeFound)
            {
                adjacentNodeFound = false;
                std::shuffle(begin(directions), end(directions), randomEngine);

                for (NodeValue direction : directions)
                {
                    if (auto [nx, ny] = getAdjacentCoordinates(x, y, direction); isWithinGridBounds(nx, ny, width, height) && grid[ny][nx] == NodeValue::none)
                    {
                        addAdjacentNodePath(x, y, nx, ny, direction, grid);

                        if (callback)
                        {
                            invokeNodePairCallback(x, y, nx, ny, grid, *callback);
                        }

                        x = nx;
                        y = ny;
                        adjacentNodeFound = true;
                        break;
                    }
                }
            }

            utility::logInfo("Walking Ended");
        }

        /// @brief Get adjacent nodes that have already been visited
        /// @param x Node x coordinate
        /// @param y Node y coordinate
        /// @param directions Directions to reach adjacent node
        /// @param width Grid width
        /// @param height Grid height
        /// @param grid Grid representing maze
        /// @return Vector of visited adjacent nodes
        std::vector<NodeValue> getVisitedAdjacentNodes(int x, int y, Directions& directions, int width, int height, Grid& grid)
        {
            Directions adjacentNodes{};

            for (NodeValue direction : directions)
            {
                auto [nx, ny] = getAdjacentCoordinates(x, y, direction);

                if (isWithinGridBounds(nx, ny, width, height) && grid[ny][nx] != NodeValue::none)
                {
                    adjacentNodes.push_back(direction);
                }
            }

            return adjacentNodes;
        }

        /// @brief Hunt for unvisited node with a visited adjacent node
        /// @param grid Maze grid representation
        /// @param directions Directions to reach adjacent node
        /// @param width Grid width
        /// @param height Grid height
        /// @param randomEngine Random number generator used for shuffling
        /// @param callback User defined callback nullptr if callback should be invoked after maze generation
        /// @return Node coordinate or std::nullopt if no node is found
        std::optional<NodeCoordinates> hunt(Grid& grid, Directions& directions, int width, int height, std::default_random_engine& randomEngine, MazeCallback* callback)
        {
            utility::logInfo("Hunting Started");

            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    if (grid[y][x] != NodeValue::none)
                    {
                        continue;
                    }

                    std::shuffle(begin(directions), end(directions), randomEngine);
                    std::vector<NodeValue> adjacentNodes = getVisitedAdjacentNodes(x, y, directions, width, height, grid);

                    if (adjacentNodes.size() == 0)
                    {
                        continue;
                    }

                    NodeValue randomDirection = adjacentNodes[math::Random::generateNumber(0, adjacentNodes.size())];
                    auto [nx, ny] = getAdjacentCoordinates(x, y, randomDirection);
                    addAdjacentNodePath(x, y, nx, ny, randomDirection, grid);

                    if (callback)
                    {
                        invokeNodePairCallback(x, y, nx, ny, grid, *callback);
                    }

                    utility::logInfo("Hunting Succeeded");
                    return NodeCoordinates(x, y);
                }
            }

            utility::logInfo("Hunting Failed");
            return std::nullopt;
        }
    }

    void huntAndKill(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        utility::logInfo("Hunt And Kill Maze Generation Started");

        Grid grid = generateGrid(width, height);
        Directions directions = getDefaultDirections();
        std::default_random_engine randomEngine{ math::Random::seed };

        std::optional<NodeCoordinates> xYCoordinate{ getRandomStartingNode(width, height) };
        MazeCallback* callbackPtr = invokeAfterGeneration ? nullptr : &callback;

        while (xYCoordinate.has_value())
        {
            const auto& [x, y] = xYCoordinate.value();
            walk(x, y, grid, directions, randomEngine, callbackPtr);
            xYCoordinate = hunt(grid, directions, width, height, randomEngine, callbackPtr);
        }

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }

        utility::logInfo("Hunt And Kill Maze Generation Ended");
    }
}
