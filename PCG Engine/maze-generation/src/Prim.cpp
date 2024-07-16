#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/Prim.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <tuple>

namespace pcg::engine::maze_generation
{
    namespace
    {
        using NodesVector = std::vector<NodeCoordinates>;

        /// @brief Add node to frontiers vector
        /// @param x Node x coordinate
        /// @param y Node y coordinate
        /// @param frontiers Frontiers node vector
        /// @param grid Grid representing maze
        void addFrontierNode(int x, int y, NodesVector& frontiers, Grid& grid)
        {
            const int width = grid[0].size();
            const int height = grid.size();

            if (isWithinGridBounds(x, y, width, height) && grid[y][x] == NodeValue::none)
            {
                grid[y][x] |= NodeValue::frontier;
                frontiers.emplace_back(NodeCoordinates(x, y));
            }
        }

        /// @brief Mark node as part of the maze and adjacent nodes as frontiers
        /// @param x Node x coordinate
        /// @param y Node y coordinate
        /// @param frontiers Frontiers node vector
        /// @param grid Grid representing maze
        void mark(int x, int y, NodesVector& frontiers, Grid& grid)
        {
            grid[y][x] |= NodeValue::in;
            addFrontierNode(x, y + 1, frontiers, grid);
            addFrontierNode(x, y - 1, frontiers, grid);
            addFrontierNode(x + 1, y, frontiers, grid);
            addFrontierNode(x - 1, y, frontiers, grid);
        }

        /// @brief Mark random node in grid as in
        /// @param width Grid width
        /// @param height Grid height
        /// @param frontierNodes Frontiers node vector
        /// @param grid Grid representing maze
        void markRandomStartingNode(int width, int height, NodesVector& frontierNodes, Grid& grid)
        {
            auto [randomX, randomY] = getRandomStartingNode(width, height);
            mark(randomX, randomY, frontierNodes, grid);
        }

        /// @brief Check that node is in maze
        /// @param x Node x coordinate
        /// @param y Node y coordinate
        /// @param grid Grid representing maze
        /// @return True if node is marked as in
        bool isInMaze(int x, int y, const Grid& grid)
        {
            return (grid[y][x] & NodeValue::in) != NodeValue::none;
        }

        /// @brief Get an adjacent node that is marked as in
        /// @param x Node x coordinate
        /// @param y Node y coordinate
        /// @param grid Grid representing maze
        /// @return An adjacent node marked as in and the direction from node to adjacent
        std::tuple<int, int, NodeValue> getAdjacentNode(int x, int y, const Grid& grid)
        {
            std::vector<std::tuple<int, int, NodeValue>> adjacentsNodes{};

            const int leftX = x - 1;
            const int rightX = x + 1;
            const int forwardY = y + 1;
            const int backwardY = y - 1;

            if (x > 0 && isInMaze(leftX, y, grid))
            {
                adjacentsNodes.emplace_back(std::make_tuple(leftX, y, NodeValue::left));
            }

            if (rightX < grid[0].size() && isInMaze(rightX, y, grid))
            {
                adjacentsNodes.emplace_back(std::make_tuple(rightX, y, NodeValue::right));
            }

            if (y > 0 && isInMaze(x, backwardY, grid))
            {
                adjacentsNodes.emplace_back(std::make_tuple(x, backwardY, NodeValue::backward));
            }

            if (forwardY < grid.size() && isInMaze(x, forwardY, grid))
            {
                adjacentsNodes.emplace_back(std::make_tuple(x, forwardY, NodeValue::forward));
            }

            return math::Random::element<std::tuple<int, int, NodeValue>>(adjacentsNodes);
        }
    }

    void prim(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        utility::logInfo("Prim Maze Generation Started");

        Grid grid = generateGrid(width, height);
        NodesVector frontierNodes{};
        markRandomStartingNode(width, height, frontierNodes, grid);

        while (!frontierNodes.empty())
        {
            const auto frontierNode = math::Random::element<NodeCoordinates>(frontierNodes);
            std::erase(frontierNodes, frontierNode);
            auto& [frontierX, frontierY] = frontierNode;
            auto [adjacentX, adjacentY, direction] = getAdjacentNode(frontierX, frontierY, grid);
            addAdjacentNodePath(frontierX, frontierY, adjacentX, adjacentY, direction, grid);

            if (!invokeAfterGeneration)
            {
                invokeNodePairCallback(frontierX, frontierY, adjacentX, adjacentY, grid, callback);
            }

            mark(frontierX, frontierY, frontierNodes, grid);
        }

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }

        utility::logInfo("Prim Maze Generation Ended");
    }
}
