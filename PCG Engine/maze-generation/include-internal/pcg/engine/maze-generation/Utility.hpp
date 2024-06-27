#ifndef PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP
#define PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    /// @brief Loops over grid and invoke callback on each node
    /// @param grid Grid representing maze
    /// @param callback User defined callback
    void invokeCallback(const Grid& grid, const MazeCallback& callback);

    /// @brief Generate a 2D vector representing the maze's grid
    /// @param width Grid width
    /// @param height Grid height
    /// @param defaultValue Default value when allocating grid
    /// @return A 2D vector representing the maze's grid
    inline Grid generateGrid(int width, int height, utility::enums::Direction defaultValue = utility::enums::Direction::none) { return Grid(height, Directions(width, defaultValue)); }

    /// @brief Get default directions used when generating maze
    /// @return a vector containing { left, right, forward, backward }
    inline Directions getDefaultDirections()
    {
        return Directions
        {
            utility::enums::Direction::left, utility::enums::Direction::right,
                utility::enums::Direction::forward, utility::enums::Direction::backward
        };
    }
}

#endif // PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP
