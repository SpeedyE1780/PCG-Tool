#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/Prim.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <tuple>

namespace pcg::engine::maze_generation
{
    namespace
    {
        using NodesVector = std::vector<std::tuple<int, int>>;

        void addFrontierNode(int x, int y, NodesVector& frontiers, Grid& grid)
        {
            const int width = grid[0].size();
            const int height = grid.size();

            if (isWithinGridBounds(x, y, width, height) && grid[y][x] == NodeValue::none)
            {
                grid[y][x] |= NodeValue::frontier;
                frontiers.emplace_back(std::make_pair(x, y));
            }
        }

        void mark(int x, int y, NodesVector& frontiers, Grid& grid)
        {
            grid[y][x] |= NodeValue::in;
            addFrontierNode(x, y + 1, frontiers, grid);
            addFrontierNode(x, y - 1, frontiers, grid);
            addFrontierNode(x + 1, y, frontiers, grid);
            addFrontierNode(x - 1, y, frontiers, grid);
        }

        void markRandomStartingNode(int width, int height, NodesVector& frontierNodes, Grid& grid)
        {
            const int randomX = math::Random::generateNumber(0, width);
            const int randomY = math::Random::generateNumber(0, height);
            mark(randomX, randomY, frontierNodes, grid);
        }

        std::tuple<int, int, NodeValue> getAdjacentNode(int x, int y, const Grid& grid)
        {
            std::vector<std::tuple<int, int, NodeValue>> adjacentsNodes{};

            const int leftX = x - 1;
            const int rightX = x + 1;
            const int forwardY = y + 1;
            const int backwardY = y - 1;

            if (x > 0 && (grid[y][leftX] & NodeValue::in) != NodeValue::none)
            {
                adjacentsNodes.emplace_back(std::make_tuple(leftX, y, NodeValue::left));
            }

            if (rightX < grid[0].size() && (grid[y][rightX] & NodeValue::in) != NodeValue::none)
            {
                adjacentsNodes.emplace_back(std::make_tuple(rightX, y, NodeValue::right));
            }

            if (y > 0 && (grid[backwardY][x] & NodeValue::in) != NodeValue::none)
            {
                adjacentsNodes.emplace_back(std::make_tuple(x, backwardY, NodeValue::backward));
            }

            if (forwardY < grid.size() && (grid[forwardY][x] & NodeValue::in) != NodeValue::none)
            {
                adjacentsNodes.emplace_back(std::make_tuple(x, forwardY, NodeValue::forward));
            }

            return adjacentsNodes[math::Random::generateNumber(0, adjacentsNodes.size())];
        }
    }

    void prim(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        Grid grid = generateGrid(width, height);
        NodesVector frontierNodes{};
        markRandomStartingNode(width, height, frontierNodes, grid);

        while (!frontierNodes.empty())
        {
            const std::tuple<int, int> frontierNode = frontierNodes[math::Random::generateNumber(0, frontierNodes.size())];
            std::erase(frontierNodes, frontierNode);
            auto& [frontierX, frontierY] = frontierNode;
            auto [adjacentX, adjacentY, direction] = getAdjacentNode(frontierX, frontierY, grid);
            grid[frontierY][frontierX] |= direction;
            grid[adjacentY][adjacentX] |= getOppositeNodeValue(direction);

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
    }
}
