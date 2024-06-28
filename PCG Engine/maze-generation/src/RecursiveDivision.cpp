#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/RecursiveDivision.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <stack>
#include <tuple>

namespace pcg::engine::maze_generation
{
    namespace
    {
        struct GridSection
        {
            bool isInvalid() const
            {
                return width == 0 || height == 0 || (width == 1 && height == 1);
            }

            int startX = 0;
            int startY = 0;
            int width = 0;
            int height = 0;
        };

        enum class WallOrientation
        {
            Horizontal = 0,
            Vertical = 1
        };

        WallOrientation chooseOrientation(int width, int height)
        {
            if (width < height)
            {
                return WallOrientation::Horizontal;
            }
            else if (height < width)
            {
                return WallOrientation::Vertical;
            }
            else
            {
                return math::Random::generateNumber(0, 2) == 0 ? WallOrientation::Horizontal : WallOrientation::Vertical;
            }
        }

        std::tuple<int, int> getWallCoordinates(const GridSection& section, bool isHorizontal)
        {
            const int wallX = section.startX + (isHorizontal ? 0 : math::Random::generateNumber(0, section.width - 1));
            const int wallY = section.startY + (isHorizontal ? math::Random::generateNumber(0, section.height - 1) : 0);

            return { wallX, wallY };
        }

        std::tuple<int, int> getPassageCoordinates(const GridSection& section, int wallX, int wallY, bool isHorizontal)
        {
            const int passageX = wallX + (isHorizontal ? math::Random::generateNumber(0, section.width) : 0);
            const int passageY = wallY + (isHorizontal ? 0 : math::Random::generateNumber(0, section.height));

            return { passageX, passageY };
        }

        GridSection getLeftBottomSection(const GridSection& section, int passageX, int passageY, bool isHorizontal)
        {
            const int startX = section.startX;
            const int startY = section.startY;
            const int width = isHorizontal ? section.width : passageX - section.startX + 1;
            const int height = isHorizontal ? passageY - section.startY + 1 : section.height;

            return { startX, startY, width, height };
        }

        GridSection getRightTopSection(const GridSection& section, int adjacentX, int adjacentY, bool isHorizontal)
        {
            const int startX = isHorizontal ? section.startX : adjacentX;
            const int startY = isHorizontal ? adjacentY : section.startY;
            const int width = isHorizontal ? section.width : section.startX + section.width - adjacentX;
            const int height = isHorizontal ? section.startY + section.height - adjacentY : section.height;

            return { startX, startY, width, height };
        }

        void addGridBounds(Grid& grid, int width, int height)
        {
            const int upperBound = height - 1;
            const int rightBound = width - 1;

            for (int x = 0; x < width; ++x)
            {
                grid[0][x] &= ~NodeValue::backward;
                grid[upperBound][x] &= ~NodeValue::forward;
            }

            for (int y = 0; y < width; ++y)
            {
                grid[y][0] &= ~NodeValue::left;
                grid[y][rightBound] &= ~NodeValue::right;
            }
        }

        void divide(Grid& grid, int width, int height, MazeCallback* callback)
        {
            std::stack<GridSection> sections{};
            sections.push({ 0, 0, width, height });

            while (!sections.empty())
            {
                const GridSection& section = sections.top();

                if (section.isInvalid())
                {
                    return;
                }

                const WallOrientation orientation = chooseOrientation(section.width, section.height);
                const bool isHorizontal = orientation == WallOrientation::Horizontal;
                const auto passageDirection = isHorizontal ? NodeValue::forward : NodeValue::right;
                const auto wallDirection = isHorizontal ? NodeValue::right : NodeValue::forward;
                auto [wallX, wallY] = getWallCoordinates(section, isHorizontal);
                const auto [passageX, passageY] = getPassageCoordinates(section, wallX, wallY, isHorizontal);
                const auto [adjacentX, adjacentY] = getAdjacentCoordinates(passageX, passageY, passageDirection);
                const int wallLength = isHorizontal ? section.width : section.height;

                for (int i = 0; i < wallLength; ++i)
                {
                    if (wallX != passageX || wallY != passageY)
                    {
                        auto [adjacentWallX, adjacentWallY] = getAdjacentCoordinates(wallX, wallY, passageDirection);
                        grid[wallY][wallX] &= ~passageDirection;
                        grid[adjacentWallY][adjacentWallX] &= ~flipNodeValue(passageDirection);

                        if (callback)
                        {
                            (*callback)(wallX, wallY, grid[wallY][wallX]);
                            (*callback)(adjacentWallX, adjacentWallY, grid[adjacentWallY][adjacentWallX]);
                        }
                    }
                    else if (callback)
                    {
                        auto [adjacentWallX, adjacentWallY] = getAdjacentCoordinates(wallX, wallY, passageDirection);
                        (*callback)(wallX, wallY, grid[wallY][wallX]);
                        (*callback)(adjacentWallX, adjacentWallY, grid[adjacentWallY][adjacentWallX]);
                    }

                    std::tie(wallX, wallY) = getAdjacentCoordinates(wallX, wallY, wallDirection);
                }

                GridSection leftBottomSection = getLeftBottomSection(section, passageX, passageY, isHorizontal);
                GridSection rightTopSection = getRightTopSection(section, adjacentX, adjacentY, isHorizontal);
                sections.pop();
                sections.emplace(std::move(leftBottomSection));
                sections.emplace(std::move(rightTopSection));
            }

        }
    }

    void recursiveDivision(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        Grid grid = generateGrid(width, height, NodeValue::right | NodeValue::left | NodeValue::forward | NodeValue::backward);
        addGridBounds(grid, width, height);

        divide(grid, width, height, invokeAfterGeneration ? nullptr : &callback);

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }
    }
}
