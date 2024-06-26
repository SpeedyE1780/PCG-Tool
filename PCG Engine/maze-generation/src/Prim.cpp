#include <pcg/engine/maze-generation/Prim.hpp>

#include <pcg/engine/math/random.hpp>

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

            if (x >= 0 && x < width && y >= 0 && y < height && grid[y][x] == utility::enums::Direction::none)
            {
                grid[y][x] |= static_cast<utility::enums::Direction>(frontier);
                frontiers.emplace_back(std::make_pair(x, y));
            }
        }

        void mark(int x, int y, NodesVector& frontiers, Grid& grid)
        {
            grid[y][x] |= static_cast<utility::enums::Direction>(in);
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

        std::tuple<int, int, utility::enums::Direction> getAdjacentNode(int x, int y, const Grid& grid)
        {
            std::vector<std::tuple<int, int, utility::enums::Direction>> adjacentsNodes{};

            const int leftX = x - 1;
            const int rightX = x + 1;
            const int forwardY = y + 1;
            const int backwardY = y - 1;

            if (x > 0 && (static_cast<int>(grid[y][leftX]) & in) != 0)
            {
                adjacentsNodes.emplace_back(std::make_tuple(leftX, y, utility::enums::Direction::left));
            }

            if (rightX < grid[0].size() && (static_cast<int>(grid[y][rightX]) & in) != 0)
            {
                adjacentsNodes.emplace_back(std::make_tuple(rightX, y, utility::enums::Direction::right));
            }

            if (y > 0 && (static_cast<int>(grid[backwardY][x]) & in) != 0)
            {
                adjacentsNodes.emplace_back(std::make_tuple(x, backwardY, utility::enums::Direction::backward));
            }

            if (forwardY < grid.size() && (static_cast<int>(grid[forwardY][x]) & in) != 0)
            {
                adjacentsNodes.emplace_back(std::make_tuple(x, forwardY, utility::enums::Direction::forward));
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
            grid[adjacentY][adjacentX] |= utility::enums::getFlippedDirection(direction);

            if (!invokeAfterGeneration)
            {
                callback(frontierX, frontierY, grid[frontierY][frontierX]);
                callback(adjacentX, adjacentY, grid[adjacentY][adjacentX]);
            }

            mark(frontierX, frontierY, frontierNodes, grid);
        }

        if (invokeAfterGeneration)
        {
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    callback(x, y, grid[y][x]);
                }
            }
        }
    }
}
