#include <pcg/engine/core/Maze.hpp>

#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <map>
#include <random>
#include <sstream>
#include <vector>

namespace pcg::engine::core
{
    namespace
    {
        static constexpr int left = 1 << 0;
        static constexpr int right = 1 << 1;
        static constexpr int up = 1 << 2;
        static constexpr int down = 1 << 3;
        static constexpr int in = 1 << 6;

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

        std::tuple<int, int> getNeighborXY(int x, int y, int direction)
        {
            const math::Vector3& directionVector = getDirection(direction);
            int nx = x + directionVector.x;
            int ny = y + directionVector.y;
            return { nx, ny };
        }

        struct WilsonWalkData
        {
            int x;
            int y;
            int direction;
        };

        std::vector<WilsonWalkData> wilsonWalk(const std::vector<std::vector<int>>& grid, std::vector<int>& directions, std::default_random_engine& randomEngine)
        {
            const int width = grid.size();
            const int height = grid[0].size();
            int x = 0;
            int y = 0;

            do
            {
                x = randomEngine() % width;
                y = randomEngine() % height;
            } while (grid[y][x] != 0);

            int startX = x;
            int startY = y;
            bool walking = true;

            std::map<std::tuple<int, int>, int> visits;
            visits[{x, y}] = 0;

            while (walking)
            {
                walking = false;
                std::shuffle(begin(directions), end(directions), randomEngine);

                for (int direction : directions)
                {
                    auto [nx, ny] = getNeighborXY(x, y, direction);

                    if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                    {
                        visits[{x, y}] = direction;

                        if (grid[ny][nx] != 0)
                        {
                            break;
                        }
                        else
                        {
                            x = nx;
                            y = ny;
                            walking = true;
                            break;
                        }
                    }
                }
            }

            std::vector<WilsonWalkData> path{};

            x = startX;
            y = startY;

            while (visits.find({ x, y }) != visits.end())
            {
                std::ostringstream oss{};
                int direction = visits[{x, y}];
                oss << "Adding: " << x << "-" << y << ": " << direction << " to path";
                utility::logInfo(oss.str());

                path.emplace_back(WilsonWalkData{ x, y, direction });
                std::tie(x, y) = getNeighborXY(x, y, direction);
            }

            return path;
        }
    }

    void aldousBroder(int width, int height, addMazePointCallback callback)
    {
        std::ostringstream oss{};

        utility::logInfo("Aldous - Broder Maze Generation Started");

        std::vector<int> directions{ left, right, up, down };
        auto randomDevice = std::random_device{};
        auto randomEngine = std::default_random_engine{ randomDevice() };

        std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));

        int x = randomEngine() % width;
        int y = randomEngine() % height;
        int unvisited = width * height - 1;

        oss << "Started with:" << x << "-" << y << " unvisited: " << unvisited;
        utility::logInfo(oss.str());
        oss.str("");

        while (unvisited > 0)
        {
            std::shuffle(begin(directions), end(directions), randomEngine);

            for (int direction : directions)
            {
                auto [nx, ny] = getNeighborXY(x, y, direction);

                if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                {
                    if (grid[ny][nx] == 0)
                    {
                        grid[y][x] |= direction;
                        grid[ny][nx] |= getFlippedDirection(direction);
                        unvisited -= 1;
                        oss << "Value set at " << x << "-" << y << "/" << nx << "-" << ny << " unvisited: " << unvisited;
                        utility::logInfo(oss.str());
                        oss.str("");
                        callback(x, y, grid[y][x]);
                        callback(nx, ny, grid[ny][nx]);
                    }

                    x = nx;
                    y = ny;
                    break;
                }
            }
        }

        utility::logInfo("Aldous - Broder Maze Generation Ended");
    }

    void wilson(int width, int height, addMazePointCallback callback)
    {
        utility::logInfo("Wilson Maze Generation Started");

        std::ostringstream oss{};
        std::vector<int> directions{ left, right, up, down };
        auto randomDevice = std::random_device{};
        auto randomEngine = std::default_random_engine{ randomDevice() };

        std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));
        int x = randomEngine() % width;
        int y = randomEngine() % height;
        int unvisited = width * height - 1;

        grid[y][x] = in;

        oss << "Started with:" << x << "-" << y << " unvisited: " << unvisited;
        utility::logInfo(oss.str());
        oss.str("");

        while (unvisited > 0)
        {
            for (const auto& walkData : wilsonWalk(grid, directions, randomEngine))
            {
                int x = walkData.x;
                int y = walkData.y;
                auto [nx, ny] = getNeighborXY(x, y, walkData.direction);
                grid[y][x] |= walkData.direction;
                grid[ny][nx] |= getFlippedDirection(walkData.direction);
                oss << "Value set at " << x << "-" << y << "/" << nx << "-" << ny << " unvisited: " << unvisited;
                utility::logInfo(oss.str());
                oss.str("");
                callback(x, y, grid[y][x]);
                callback(nx, ny, grid[ny][nx]);
                unvisited -= 1;
            }
        }

        utility::logInfo("Wilson Maze Generation Ended");
    }

    void binaryTree(int width, int height, addMazePointCallback callback)
    {
        std::vector<int> directions{ right, up };
        std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));
        auto randomDevice = std::random_device{};
        auto randomEngine = std::default_random_engine{ randomDevice() };

        for (int h = 0; h < height; ++h)
        {
            for (int w = 0; w < width; ++w)
            {
                std::shuffle(begin(directions), end(directions), randomEngine);

                for (int direction : directions)
                {
                    auto [nw, nh] = getNeighborXY(w, h, direction);

                    if (nw >= 0 && nh >= 0 && nw < width && nh < height)
                    {
                        grid[h][w] |= direction;
                        grid[nh][nw] |= getFlippedDirection(direction);
                        callback(w, h, grid[h][w]);
                        callback(nw, nh, grid[nh][nw]);
                        break;
                    }
                }
            }
        }
    }
}
