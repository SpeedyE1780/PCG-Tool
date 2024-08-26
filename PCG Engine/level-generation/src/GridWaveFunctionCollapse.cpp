#include <pcg/engine/level-generation/GridWaveFunctionCollapse.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <functional>
#include <optional>
#include <queue>
#include <random>
#include <sstream>
#include <stack>
#include <unordered_map>

namespace pcg::engine::level_generation
{
    namespace
    {
        using Grid2D = std::vector<std::vector<utility::enums::Direction>>;
        using Pending2DNode = std::queue<std::tuple<int, int>>;
        using GridNodeValue = std::tuple<int, int, utility::enums::Direction>;
        using BoundCheckCallback = std::function<bool(int, int, utility::enums::Direction)>;
        using GetAdjacentNodeCallback = std::function<GridNodeValue(int, int, utility::enums::Direction)>;

        /// @brief Get directions from chosen axes
        /// @param axes Axes that will be used to generate level
        /// @return Vector containing all directions used
        std::vector<utility::enums::Direction> getDirections(math::Axis axes)
        {
            std::vector<utility::enums::Direction> directions{};

            if (utility::enums::hasFlag(axes, math::Axis::positiveX))
            {
                directions.emplace_back(utility::enums::Direction::right);
            }

            if (utility::enums::hasFlag(axes, math::Axis::negativeX))
            {
                directions.emplace_back(utility::enums::Direction::left);
            }

            if (utility::enums::hasFlag(axes, math::Axis::positiveY))
            {
                directions.emplace_back(utility::enums::Direction::up);
            }

            if (utility::enums::hasFlag(axes, math::Axis::negativeY))
            {
                directions.emplace_back(utility::enums::Direction::down);
            }

            if (utility::enums::hasFlag(axes, math::Axis::positiveZ))
            {
                directions.emplace_back(utility::enums::Direction::forward);
            }

            if (utility::enums::hasFlag(axes, math::Axis::negativeZ))
            {
                directions.emplace_back(utility::enums::Direction::backward);
            }

            return directions;
        }

        /// @brief Get directions from chosen plane
        /// @param plane Plane that will be used to generate level
        /// @return Vector containing all directions used
        std::vector<utility::enums::Direction> getDirections(math::Plane plane)
        {
            return getDirections(static_cast<math::Axis>(plane));
        }

        bool isAdjacentOutOfXBounds(int x, int width, utility::enums::Direction direction)
        {
            return x == 0 && utility::enums::hasFlag(direction, utility::enums::Direction::left) ||
                x == width - 1 && utility::enums::hasFlag(direction, utility::enums::Direction::right);
        }

        bool isAdjacentOutOfYBounds(int y, int height, utility::enums::Direction direction)
        {
            return y == 0 && utility::enums::hasFlag(direction, utility::enums::Direction::down)
                || y == height - 1 && utility::enums::hasFlag(direction, utility::enums::Direction::up);
        }

        bool isAdjacentOutOfZBounds(int z, int depth, utility::enums::Direction direction)
        {
            return z == 0 && utility::enums::hasFlag(direction, utility::enums::Direction::backward)
                || z == depth - 1 && utility::enums::hasFlag(direction, utility::enums::Direction::forward);
        }

        int getAdjacentOnXAxis(int x, utility::enums::Direction direction)
        {
            if (utility::enums::hasFlag(direction, utility::enums::Direction::left))
            {
                return x - 1;
            }
            else if (utility::enums::hasFlag(direction, utility::enums::Direction::right))
            {
                return x + 1;
            }

            return x;
        }

        int getAdjacentOnYAxis(int y, utility::enums::Direction direction)
        {
            if (utility::enums::hasFlag(direction, utility::enums::Direction::up))
            {
                return y + 1;
            }
            else if (utility::enums::hasFlag(direction, utility::enums::Direction::down))
            {
                return y - 1;
            }

            return y;
        }

        int getAdjacentOnZAxis(int z, utility::enums::Direction direction)
        {
            if (utility::enums::hasFlag(direction, utility::enums::Direction::forward))
            {
                return z + 1;
            }
            else if (utility::enums::hasFlag(direction, utility::enums::Direction::backward))
            {
                return z - 1;
            }

            return z;
        }

        GridNodeValue getAdjacentOnXYPlane(int x, int y, utility::enums::Direction direction)
        {
            x = getAdjacentOnXAxis(x, direction);
            y = getAdjacentOnYAxis(y, direction);
            direction = utility::enums::getFlippedDirection(direction);
            return { x, y, direction };
        }

        GridNodeValue getAdjacentOnXZPlane(int x, int y, utility::enums::Direction direction)
        {
            x = getAdjacentOnXAxis(x, direction);
            y = getAdjacentOnZAxis(y, direction);
            direction = utility::enums::getFlippedDirection(direction);
            return { x, y, direction };
        }

        GridNodeValue getAdjacentOnYZPlane(int x, int y, utility::enums::Direction direction)
        {
            x = getAdjacentOnYAxis(x, direction);
            y = getAdjacentOnZAxis(y, direction);
            direction = utility::enums::getFlippedDirection(direction);
            return { x, y, direction };
        }

        class Grid2DGenerator
        {
        public:
            Grid2DGenerator(int width, int height, const std::function<void(int, int, utility::enums::Direction)>& callback, math::Plane plane) :
                grid(height, std::vector<utility::enums::Direction>(width, utility::enums::Direction::none)),
                width(width),
                height(height),
                callback(callback),
                x(math::Random::number(width)),
                y(math::Random::number(height)),
                randomEngine(math::Random::getDefaultEngine()),
                directions(getDirections(plane))
            {
                std::shuffle(begin(directions), end(directions), randomEngine);
                pending.emplace(std::make_pair(x, y));
                setCallbacks(plane);
            }

            void operator()()
            {
                while (!pending.empty())
                {
                    std::tie(x, y) = pending.front();
                    pending.pop();
                    const int adjacents = math::Random::number(directions.size());

                    for (int i = 0; i < adjacents; ++i)
                    {
                        direction = directions[i];
                        processNode();
                    }

                    std::shuffle(begin(directions), end(directions), randomEngine);
                }
            }

            bool isOutOfBounds() const
            {
                return firstAxisCheck(x, width, direction) || secondAxisCheck(y, height, direction);
            }

            bool hasFlag() const
            {
                return utility::enums::hasFlag(grid[y][x], direction);
            }

            void updateNodesValue()
            {
                updateNodeValue();
                updateAdjacentNodeValue();
            }

            void updateNodeValue()
            {
                grid[y][x] |= direction;

                if (callback)
                {
                    invokeCallback();
                }
            }

            void updateAdjacentNodeValue()
            {
                auto [adjacentX, adjacentY, adjacentDirection] = getAdjacentNode(x, y, direction);
                grid[adjacentY][adjacentX] |= adjacentDirection;
                pending.emplace(std::make_pair(adjacentX, adjacentY));

                if (callback)
                {
                    invokeCallback();
                }
            }

            void invokeCallback()
            {
                callback(x, y, grid[y][x]);
            }

            void invokeGridCallback(const std::function<void(int, int, utility::enums::Direction)>& delayedCallback)
            {
                for (int y = 0; y < height; ++y)
                {
                    for (int x = 0; x < width; ++x)
                    {
                        delayedCallback(x, y, grid[y][x]);
                    }
                }
            }

        private:
            void setCallbacks(math::Plane plane)
            {
                switch (plane)
                {
                case math::Plane::xy:
                {
                    firstAxisCheck = isAdjacentOutOfXBounds;
                    secondAxisCheck = isAdjacentOutOfYBounds;
                    getAdjacentNode = getAdjacentOnXYPlane;
                    break;
                }
                case math::Plane::xz:
                {
                    firstAxisCheck = isAdjacentOutOfXBounds;
                    secondAxisCheck = isAdjacentOutOfZBounds;
                    getAdjacentNode = getAdjacentOnXZPlane;
                    break;
                }
                case math::Plane::yz:
                {
                    firstAxisCheck = isAdjacentOutOfYBounds;
                    secondAxisCheck = isAdjacentOutOfZBounds;
                    getAdjacentNode = getAdjacentOnYZPlane;
                    break;
                }
                default:
                {
                    utility::logError("Wrong Axis given to Grid2DGenerator.setCallbacks");
                    break;
                }
                }
            }

            void processNode()
            {
                if (isOutOfBounds() || hasFlag())
                {
                    return;
                }

                updateNodesValue();
            }

            Grid2D grid;
            int width;
            int height;
            std::function<void(int, int, utility::enums::Direction)> callback;
            int x;
            int y;
            std::default_random_engine randomEngine;
            std::vector<utility::enums::Direction> directions;
            utility::enums::Direction direction = utility::enums::Direction::none;
            Pending2DNode pending{};
            BoundCheckCallback firstAxisCheck = nullptr;
            BoundCheckCallback secondAxisCheck = nullptr;
            GetAdjacentNodeCallback getAdjacentNode = nullptr;
        };

        void processNode(std::vector<std::vector<std::vector<utility::enums::Direction>>>& grid, std::queue<std::tuple<int, int, int>>& pending, int x, int y, int z, utility::enums::Direction direction, const std::function<void(int, int, int, utility::enums::Direction)>& callback)
        {
            if (x == 0 && utility::enums::hasFlag(direction, utility::enums::Direction::left)
                || x == grid[z][y].size() - 1 && utility::enums::hasFlag(direction, utility::enums::Direction::right)
                || y == 0 && utility::enums::hasFlag(direction, utility::enums::Direction::down)
                || y == grid[z].size() - 1 && utility::enums::hasFlag(direction, utility::enums::Direction::up)
                || z == 0 && utility::enums::hasFlag(direction, utility::enums::Direction::backward)
                || z == grid.size() - 1 && utility::enums::hasFlag(direction, utility::enums::Direction::forward)
                || utility::enums::hasFlag(grid[z][y][x], direction))
            {
                return;
            }

            grid[z][y][x] |= direction;
            if (callback)
            {
                callback(x, y, z, grid[z][y][x]);
            }

            if (utility::enums::hasFlag(direction, utility::enums::Direction::left))
            {
                x -= 1;
                direction = utility::enums::Direction::right;
            }
            else if (utility::enums::hasFlag(direction, utility::enums::Direction::right))
            {
                x += 1;
                direction = utility::enums::Direction::left;
            }
            else if (utility::enums::hasFlag(direction, utility::enums::Direction::up))
            {
                y += 1;
                direction = utility::enums::Direction::down;
            }
            else if (utility::enums::hasFlag(direction, utility::enums::Direction::down))
            {
                y -= 1;
                direction = utility::enums::Direction::up;
            }
            else if (utility::enums::hasFlag(direction, utility::enums::Direction::forward))
            {
                z += 1;
                direction = utility::enums::Direction::backward;
            }
            else if (utility::enums::hasFlag(direction, utility::enums::Direction::backward))
            {
                z -= 1;
                direction = utility::enums::Direction::forward;
            }

            grid[z][y][x] |= direction;
            if (callback)
            {
                callback(x, y, z, grid[z][y][x]);
            }
            pending.emplace(std::make_tuple(x, y, z));
        }
    }

    void waveFunctionCollapse(int width, int height, math::Plane plane, bool invokeAfterGeneration, const std::function<void(int, int, utility::enums::Direction)>& callback)
    {
        utility::logInfo("2D Wave Function Collapse Started");

        Grid2DGenerator grid(width, height, invokeAfterGeneration ? nullptr : callback, plane);
        grid();

        if (invokeAfterGeneration)
        {
            grid.invokeGridCallback(callback);
        }

        utility::logInfo("2D Wave Function Collapse Ended");
    }

    void waveFunctionCollapse(int width, int height, int depth, bool invokeAfterGeneration, const std::function<void(int, int, int, utility::enums::Direction)>& callback)
    {
        utility::logInfo("3D Wave Function Collapse Started");

        std::default_random_engine randomEngine = math::Random::getDefaultEngine();
        std::vector<utility::enums::Direction> directions = getDirections(math::Axis::xyz);
        std::shuffle(begin(directions), end(directions), randomEngine);
        std::vector<std::vector<std::vector<utility::enums::Direction>>> grid(depth,
            std::vector<std::vector<utility::enums::Direction>>(height, std::vector<utility::enums::Direction>(width, utility::enums::Direction::none)));

        const int startX = math::Random::number(width);
        const int startY = math::Random::number(height);
        const int startZ = math::Random::number(depth);
        std::queue<std::tuple<int, int, int>> pending;
        pending.emplace(std::make_tuple(startX, startY, startZ));

        while (!pending.empty())
        {
            const auto& [x, y, z] = std::move(pending.front());
            pending.pop();

            const int adjacents = math::Random::number(directions.size());

            for (int i = 0; i < adjacents; ++i)
            {
                processNode(grid, pending, x, y, z, directions[i], invokeAfterGeneration ? nullptr : callback);
            }

            std::shuffle(begin(directions), end(directions), randomEngine);
        }

        if (invokeAfterGeneration)
        {
            for (int z = 0; z < depth; ++z)
            {
                for (int y = 0; y < height; ++y)
                {
                    for (int x = 0; x < width; ++x)
                    {
                        callback(x, y, z, grid[z][y][x]);
                    }
                }
            }
        }

        utility::logInfo("3D Wave Function Collapse Ended");
    }
}
