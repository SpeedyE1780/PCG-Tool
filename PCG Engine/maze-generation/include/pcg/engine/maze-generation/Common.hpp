#ifndef PCG_ENGINE_MAZE_GENERATION_COMMON_HPP
#define PCG_ENGINE_MAZE_GENERATION_COMMON_HPP

#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>
#include <pcg/engine/utility/Enums.hpp>

#include <tuple>
#include <vector>

namespace pcg::engine::maze_generation
{
    /// @brief Direction vector alias
    using Directions = std::vector<utility::enums::Direction>;
    /// @brief 2D vector alias
    using Grid = std::vector<Directions>;
    /// @brief Callback used to notify a node was spawned/modified
    using MazeCallback = utility::CallbackFunctor<void(int, int, utility::enums::Direction)>;

    /// @brief Defines a node as part of the maze without having an actual direction
    inline constexpr int in = 1 << 6;

    /// @brief Get adjacent node x, y coordinates
    /// @param x Current node x coordinate
    /// @param y Current node y coordinate
    /// @param direction Direction from current node to adjacent node
    /// @return tuple containing adjacent node x, y coordinate
    std::tuple<int, int> getAdjacentCoordinates(int x, int y, utility::enums::Direction direction);
    /// @brief Generate a 2D vector representing the maze's grid
    /// @param width Grid width
    /// @param height Grid height
    /// @param defaultValue Default value when allocating grid
    /// @return A 2D vector representing the maze's empty grid
    inline constexpr Grid generateGrid(int width, int height, utility::enums::Direction defaultValue = utility::enums::Direction::none) { return Grid(height, Directions(width, defaultValue)); }
    /// @brief Get default directions used when generating maze
    /// @return a vector containing { left, right, forward, backward }
    inline constexpr Directions getDefaultDirections()
    {
        return Directions
        {
            utility::enums::Direction::left, utility::enums::Direction::right,
                utility::enums::Direction::forward, utility::enums::Direction::backward
        };
    }
}

#endif // PCG_ENGINE_MAZE_GENERATION_COMMON_HPP
