#include <pcg/engine/maze-generation/GrowingTree.hpp>

#include <pcg/engine/math/random.hpp>

#include <functional>
#include <random>
#include <tuple>

namespace pcg::engine::maze_generation
{
    namespace
    {
        std::tuple<int, int> getRandomNode(int width, int height)
        {
            const int x = math::Random::generateNumber(0, width);
            const int y = math::Random::generateNumber(0, height);
            return { x, y };
        }

        std::tuple<int, int> getOldestNode(const std::vector<std::tuple<int, int>>& nodes)
        {
            return nodes[0];
        }

        std::tuple<int, int> getMiddleNode(const std::vector<std::tuple<int, int>>& nodes)
        {
            return nodes[nodes.size() / 2];
        }

        std::tuple<int, int> getNewestNode(const std::vector<std::tuple<int, int>>& nodes)
        {
            return nodes[nodes.size() - 1];
        }

        void growingTree(int width, int height, bool invokeAfterGeneration, std::function<std::tuple<int, int>(const std::vector<std::tuple<int, int>>& nodes)> getNextNode, MazeCallback&& callback)
        {
            Grid grid = generateGrid(width, height);
            Directions directions = getDefaultDirections();
            std::default_random_engine randomEngine{ math::Random::seed };

            std::vector<std::tuple<int, int>> nodes{};
            nodes.emplace_back(getRandomNode(width, height));

            while (!nodes.empty())
            {
                auto [x, y] = getNextNode(nodes);

                std::shuffle(begin(nodes), end(nodes), randomEngine);
                bool noAdjacentNode = true;

                for (utility::enums::Direction direction : directions)
                {
                    auto [adjacentX, adjacentY] = getAdjacentCoordinates(x, y, direction);

                    if (adjacentX >= 0 && adjacentX < width && adjacentY >= 0 && adjacentY < height && grid[adjacentY][adjacentX] == utility::enums::Direction::none)
                    {
                        grid[y][x] |= direction;
                        grid[adjacentY][adjacentX] |= utility::enums::getFlippedDirection(direction);

                        if (!invokeAfterGeneration)
                        {
                            callback(x, y, grid[y][x]);
                            callback(adjacentX, adjacentY, grid[adjacentY][adjacentX]);
                        }

                        noAdjacentNode = false;
                        nodes.emplace_back(std::make_tuple(adjacentX, adjacentY));
                    }
                }

                if (noAdjacentNode)
                {
                    std::erase(nodes, std::tuple(x, y));
                }
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

    void growingTree(int width, int height, bool invokeAfterGeneration, GrowingTreeSelectionMethod method, MazeCallback&& callback)
    {
        switch (method)
        {
        case GrowingTreeSelectionMethod::oldest:
        {
            growingTree(width, height, invokeAfterGeneration, getOldestNode, std::move(callback));
            break;
        }
        case GrowingTreeSelectionMethod::middle:
        {
            growingTree(width, height, invokeAfterGeneration, getMiddleNode, std::move(callback));
            break;
        }
        case GrowingTreeSelectionMethod::newest:
        {
            growingTree(width, height, invokeAfterGeneration, getNewestNode, std::move(callback));
            break;
        }
        default:
        {
            break;
        }
        }
    }
}
