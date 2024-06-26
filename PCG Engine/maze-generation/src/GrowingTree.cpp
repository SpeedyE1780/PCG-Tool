#include <pcg/engine/maze-generation/GrowingTree.hpp>

#include <pcg/engine/math/random.hpp>

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

        int getIndex(int /*size*/)
        {
            return 0;
        }
    }

    void growingTree(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        Grid grid = generateGrid(width, height);
        Directions directions = getDefaultDirections();
        std::default_random_engine randomEngine{ math::Random::seed };

        std::vector<std::tuple<int, int>> nodes{};
        nodes.emplace_back(getRandomNode(width, height));

        while (!nodes.empty())
        {
            int nodeIndex = getIndex(nodes.size());
            auto& [x, y] = nodes[nodeIndex];

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
