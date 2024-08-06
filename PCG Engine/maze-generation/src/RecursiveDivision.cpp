#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/RecursiveDivision.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <stack>
#include <tuple>

namespace pcg::engine::maze_generation
{
    namespace
    {
        /// @brief GridSection represents a sub division of the grid
        struct GridSection
        {
            /// @brief Check that section is has an area greater than 1x1
            /// @return True if grid area < 1x1
            bool isInvalid() const
            {
                return width == 0 || height == 0 || (width == 1 && height == 1);
            }

            /// @brief Starting x coordinate
            int startX = 0;
            /// @brief Ending x coordinate
            int startY = 0;
            /// @brief Section width
            int width = 0;
            /// @brief Section height
            int height = 0;
        };

        enum class WallOrientation
        {
            Horizontal = 0,
            Vertical = 1
        };

        /// @brief Choose an orientation for the grid division
        /// @param width Section width
        /// @param height Section height
        /// @return The chosen orientation
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
                return math::Random::boolean() ? WallOrientation::Horizontal : WallOrientation::Vertical;
            }
        }

        /// @brief Get the wall coordinates
        /// @param section Section that is being divided in 2
        /// @param isHorizontal Is wall horizontal?
        /// @return The starting position of the wall
        NodeCoordinates getWallCoordinates(const GridSection& section, bool isHorizontal)
        {
            const int wallX = section.startX + (isHorizontal ? 0 : math::Random::number(section.width - 1));
            const int wallY = section.startY + (isHorizontal ? math::Random::number(section.height - 1) : 0);

            return { wallX, wallY };
        }

        /// @brief Get the passage coordinates
        /// @param section Section that is being divided in 2
        /// @param wallX Wall x coordinate
        /// @param wallY Wall y coordinate
        /// @param isHorizontal Is passage horizontal?
        /// @return The position of the passage
        NodeCoordinates getPassageCoordinates(const GridSection& section, int wallX, int wallY, bool isHorizontal)
        {
            const int passageX = wallX + (isHorizontal ? math::Random::number(section.width) : 0);
            const int passageY = wallY + (isHorizontal ? 0 : math::Random::number(section.height));

            return { passageX, passageY };
        }

        /// @brief Get the left/bottom section
        /// @param section Section that was divided
        /// @param passageX X coordinate of passage
        /// @param passageY Y coordinate of passage
        /// @param isHorizontal Is division horizontal?
        /// @return Left/Bottom grid section
        GridSection getLeftBottomSection(const GridSection& section, int passageX, int passageY, bool isHorizontal)
        {
            const int startX = section.startX;
            const int startY = section.startY;
            const int width = isHorizontal ? section.width : passageX - section.startX + 1;
            const int height = isHorizontal ? passageY - section.startY + 1 : section.height;

            return { startX, startY, width, height };
        }

        /// @brief Get the right/top section
        /// @param section Section that was divided
        /// @param adjacentX X coordinate adjacent to passage
        /// @param adjacentY Y coordinate adjacent to passage
        /// @param isHorizontal Is division horizontal?
        /// @return Right/Top grid section
        GridSection getRightTopSection(const GridSection& section, int adjacentX, int adjacentY, bool isHorizontal)
        {
            const int startX = isHorizontal ? section.startX : adjacentX;
            const int startY = isHorizontal ? adjacentY : section.startY;
            const int width = isHorizontal ? section.width : section.startX + section.width - adjacentX;
            const int height = isHorizontal ? section.startY + section.height - adjacentY : section.height;

            return { startX, startY, width, height };
        }

        /// @brief Divide grid in multiple sections
        /// @param grid Grid representing maze
        /// @param width Grid width
        /// @param height Grid height
        /// @param callback User defined callback nullptr if callback should be invoked after maze generation
        void divide(Grid& grid, int width, int height, MazeCallback* callback)
        {
            std::stack<GridSection> sections{};
            sections.push({ 0, 0, width, height });

            while (!sections.empty())
            {
                GridSection section = std::move(sections.top());
                sections.pop();

                if (section.isInvalid())
                {
                    continue;
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
                    auto [adjacentWallX, adjacentWallY] = getAdjacentCoordinates(wallX, wallY, passageDirection);

                    if (wallX != passageX || wallY != passageY)
                    {
                        addAdjacentNodeWall(wallX, wallY, adjacentWallX, adjacentWallY, passageDirection, grid);
                    }

                    if (callback)
                    {
                        invokeNodePairCallback(wallX, wallY, adjacentWallX, adjacentWallY, grid, *callback);
                    }

                    std::tie(wallX, wallY) = getAdjacentCoordinates(wallX, wallY, wallDirection);
                }

                sections.emplace(getLeftBottomSection(section, passageX, passageY, isHorizontal));
                sections.emplace(getRightTopSection(section, adjacentX, adjacentY, isHorizontal));
            }

        }
    }

    void recursiveDivision(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        utility::logInfo("Recursive Division Maze Generation Started");
        Grid grid = generateOpenGrid(width, height);
        divide(grid, width, height, invokeAfterGeneration ? nullptr : &callback);

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }

        utility::logInfo("Recursive Division Maze Generation Ended");
    }
}
