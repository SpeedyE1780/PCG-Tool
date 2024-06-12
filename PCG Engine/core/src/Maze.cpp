#include <pcg/engine/core/Maze.hpp>

#include <pcg/engine/math/vector3.hpp>

#include <random>
#include <vector>

namespace pcg::engine::core
{
    namespace
    {
        static constexpr int left = 1 << 0;
        static constexpr int right = 1 << 1;
        static constexpr int up = 1 << 2;
        static constexpr int down = 1 << 3;

        const math::Vector3& getDirection(int direction)
        {
            switch (direction)
            {
            case left:
            {
                return math::Vector3::left;
            }
            case right:
            {
                return math::Vector3::right;
            }
            case up:
            {
                return math::Vector3::up;
            }
            case down:
            {
                return math::Vector3::down;
            }
            default:
            {
                return math::Vector3::left;
            }
            }
        }

        int getFlippedDirection(int direction)
        {
            switch (direction)
            {
            case left:
            {
                return right;
            }
            case right:
            {
                return left;
            }
            case up:
            {
                return down;
            }
            case down:
            {
                return up;
            }
            default:
            {
                return left;
            }
            }
        }
    }

    void aldousBroder(int width, int height, addMazePointCallback callback)
    {
        std::vector<int> directions{ left, right, up, down };
        auto randomDevice = std::random_device{};
        auto randomEngine = std::default_random_engine{ randomDevice() };

        std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));

        int x = randomEngine() % width;
        int y = randomEngine() % height;
        int unvisited = width * height - 1;

        while (unvisited > 0)
        {
            std::shuffle(begin(directions), end(directions), randomEngine);

            for (int direction : directions)
            {
                const auto& directionVector = getDirection(direction);

                int nx = x + directionVector.x;
                int ny = y + directionVector.y;

                if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                {
                    if (grid[ny][nx] == 0)
                    {
                        grid[y][x] |= direction;
                        grid[ny][nx] |= getFlippedDirection(direction);
                        unvisited -= 1;
                        callback(x, y, grid[y][x]);
                        callback(nx, ny, grid[ny][nx]);
                    }

                    x = nx;
                    y = ny;
                    break;
                }
            }
        }
    }
}
