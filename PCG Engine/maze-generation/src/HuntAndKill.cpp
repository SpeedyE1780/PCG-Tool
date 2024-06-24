#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/HuntAndKill.hpp>

#include <optional>
#include <random>

namespace pcg::engine::maze_generation
{
    namespace
    {
        void walk(int x, int y, Grid& grid, std::vector<utility::enums::Direction>& directions, std::default_random_engine& randomEngine, MazeCallback* callback)
        {
            const int width = grid.size();
            const int height = grid[0].size();
            bool adjacentNodeFound = true;

            while (adjacentNodeFound)
            {
                adjacentNodeFound = false;
                std::shuffle(begin(directions), end(directions), randomEngine);

                for (utility::enums::Direction direction : directions)
                {
                    auto [nx, ny] = getAdjacentCoordinates(x, y, direction);

                    if (nx >= 0 && ny >= 0 && nx < width && ny < height && grid[ny][nx] == utility::enums::Direction::none)
                    {
                        grid[y][x] |= direction;
                        grid[ny][nx] |= utility::enums::getFlippedDirection(direction);

                        if (callback)
                        {
                            (*callback)(x, y, grid[y][x]);
                            (*callback)(x, y, grid[ny][nx]);
                        }

                        x = nx;
                        y = ny;
                        adjacentNodeFound = true;
                        break;
                    }
                }
            }
        }

        std::optional<std::tuple<int, int>> hunt(Grid& grid, Directions& directions, int width, int height, std::default_random_engine& randomEngine, MazeCallback* callback)
        {
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    if (grid[y][x] != utility::enums::Direction::none)
                    {
                        continue;
                    }

                    std::shuffle(begin(directions), end(directions), randomEngine);
                    Directions adjacentNodes{};

                    for (utility::enums::Direction direction : directions)
                    {
                        auto [nx, ny] = getAdjacentCoordinates(x, y, direction);

                        if (nx >= 0 && ny >= 0 && nx < width && ny < height && grid[ny][nx] != utility::enums::Direction::none)
                        {
                            adjacentNodes.push_back(direction);
                        }
                    }

                    if (adjacentNodes.size() == 0)
                    {
                        continue;
                    }

                    utility::enums::Direction randomDirection = adjacentNodes[math::Random::generateNumber(0, adjacentNodes.size())];
                    auto [nx, ny] = getAdjacentCoordinates(x, y, randomDirection);
                    grid[y][x] |= randomDirection;
                    grid[ny][nx] |= utility::enums::getFlippedDirection(randomDirection);

                    if (callback)
                    {
                        (*callback)(x, y, grid[y][x]);
                        (*callback)(x, y, grid[ny][nx]);
                    }

                    return std::make_tuple(nx, ny);
                }
            }

            return std::nullopt;
        }
    }

    void huntAndKill(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        Grid grid = generateGrid(width, height);
        Directions directions = getDefaultDirections();
        std::default_random_engine randomEngine{ math::Random::seed };

        int x = math::Random::generateNumber(0, width);
        int y = math::Random::generateNumber(0, height);
        std::optional<std::tuple<int, int>> xYCoordinate{ { x, y } };
        MazeCallback* callbackPtr = invokeAfterGeneration ? nullptr : &callback;

        while (xYCoordinate.has_value())
        {
            const auto& [x, y] = xYCoordinate.value();
            walk(x, y, grid, directions, randomEngine, callbackPtr);
            xYCoordinate = hunt(grid, directions, width, height, randomEngine, callbackPtr);
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
