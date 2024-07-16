#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <sstream>

namespace pcg::engine::maze_generation
{
    namespace
    {
        /// @brief Get the value's opposite direction
        /// @param value The value we want to get the opposite
        /// @return The opposite of value (ex: left -> right)
        constexpr NodeValue getOppositeNodeValue(NodeValue value)
        {
            switch (value)
            {
            case NodeValue::none:
            {
                return NodeValue::none;
            }
            case NodeValue::left:
            {
                return NodeValue::right;
            }
            case NodeValue::right:
            {
                return NodeValue::left;
            }
            case NodeValue::forward:
            {
                return NodeValue::backward;
            }
            case NodeValue::backward:
            {
                return NodeValue::forward;
            }
            case NodeValue::in:
            {
                return NodeValue::in;
            }
            case NodeValue::frontier:
            {
                return NodeValue::frontier;
            }
            default:
            {
                return NodeValue::none;
            }
            }
        }

        /// @brief Add Outer edges wall to grid
        /// @param grid Grid representing maze
        /// @param width Grid Width
        /// @param height Grid Height
        void addGridBounds(Grid& grid, int width, int height)
        {
            const int upperBound = height - 1;
            const int rightBound = width - 1;

            for (int x = 0; x < width; ++x)
            {
                grid[0][x] &= ~NodeValue::backward;
                grid[upperBound][x] &= ~NodeValue::forward;
            }

            for (int y = 0; y < height; ++y)
            {
                grid[y][0] &= ~NodeValue::left;
                grid[y][rightBound] &= ~NodeValue::right;
            }
        }
    }

    void invokeNodeCallback(int x, int y, const Grid& grid, const MazeCallback& callback)
    {
        callback(x, y, grid[y][x]);
    }

    void invokeNodeCallback(const NodeCoordinates& node, const Grid& grid, const MazeCallback& callback)
    {
        invokeNodeCallback(node.x, node.y, grid, callback);
    }

    void invokeNodePairCallback(int x, int y, int adjacentX, int adjacentY, const Grid& grid, const MazeCallback& callback)
    {
        invokeNodeCallback(x, y, grid, callback);
        invokeNodeCallback(adjacentX, adjacentY, grid, callback);
    }

    void invokeNodePairCallback(const NodeCoordinates& current, const NodeCoordinates& adjacent, const Grid& grid, const MazeCallback& callback)
    {
        invokeNodePairCallback(current.x, current.y, adjacent.x, adjacent.y, grid, callback);
    }

    void invokeCallback(const Grid& grid, const MazeCallback& callback)
    {
        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = 0; x < grid[0].size(); ++x)
            {
                invokeNodeCallback(x, y, grid, callback);
            }
        }
    }

    Grid generateOpenGrid(int width, int height)
    {
        Grid grid = generateGrid(width, height, NodeValue::allDirections);
        addGridBounds(grid, width, height);
        return grid;
    }

    void addAdjacentNodePath(int nodeX, int nodeY, int adjacentNodeX, int adjacentNodeY, NodeValue direction, Grid& grid)
    {
        grid[nodeY][nodeX] |= direction;
        grid[adjacentNodeY][adjacentNodeX] |= getOppositeNodeValue(direction);

        std::ostringstream oss{};
        oss << "Path added between: (" << nodeX << ", " << nodeY << ") and (" << adjacentNodeX << ", " << adjacentNodeY << ")";
        utility::logInfo(oss.str());
    }

    void addAdjacentNodePath(const NodeCoordinates& node, const NodeCoordinates& adjacentNode, NodeValue direction, Grid& grid)
    {
        addAdjacentNodePath(node.x, node.y, adjacentNode.x, adjacentNode.y, direction, grid);
    }

    void addAdjacentNodeWall(int nodeX, int nodeY, int adjacentNodeX, int adjacentNodeY, NodeValue direction, Grid& grid)
    {
        grid[nodeY][nodeX] &= ~direction;
        grid[adjacentNodeY][adjacentNodeX] &= ~getOppositeNodeValue(direction);

        std::ostringstream oss{};
        oss << "Wall added between: (" << nodeX << ", " << nodeY << ") and (" << adjacentNodeX << ", " << adjacentNodeY << ")";
        utility::logInfo(oss.str());
    }

    NodeCoordinates getRandomStartingNode(int width, int height)
    {
        return NodeCoordinates{ math::Random::number(width), math::Random::number(height) };
    }
}
