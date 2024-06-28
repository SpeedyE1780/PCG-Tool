#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/RecursiveBacktracker.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <random>
#include <stack>

namespace pcg::engine::maze_generation
{
    void recursiveBacktracker(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        Grid grid = generateGrid(width, height);
        Directions directions = getDefaultDirections();
        std::default_random_engine randomEngine{ math::Random::seed };
        std::stack<std::tuple<int, int>> visitedNodes;

        int x = math::Random::generateNumber(0, width);
        int y = math::Random::generateNumber(0, height);

        visitedNodes.push({ x, y });

        while (!visitedNodes.empty())
        {
            auto& [x, y] = visitedNodes.top();
            std::shuffle(begin(directions), end(directions), randomEngine);
            bool noAdjacentNodes = true;

            for (NodeValue direction : directions)
            {
                auto [nx, ny] = getAdjacentCoordinates(x, y, direction);

                if (isWithinGridBounds(nx, ny, width, height) && grid[ny][nx] == NodeValue::none)
                {
                    grid[y][x] |= direction;
                    grid[ny][nx] |= getOppositeNodeValue(direction);
                    visitedNodes.push({ nx, ny });
                    noAdjacentNodes = false;

                    if (!invokeAfterGeneration)
                    {
                        callback(x, y, grid[y][x]);
                        callback(nx, ny, grid[ny][nx]);
                    }
                    break;
                }
            }

            if (noAdjacentNodes)
            {
                visitedNodes.pop();
            }
        }

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }
    }
}
