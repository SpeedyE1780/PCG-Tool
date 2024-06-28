#ifndef PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP
#define PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    /// @brief Direction vector alias
    using Directions = std::vector<NodeValue>;
    /// @brief 2D vector alias
    using Grid = std::vector<Directions>;

    /// @brief Loops over grid and invoke callback on each node
    /// @param grid Grid representing maze
    /// @param callback User defined callback
    void invokeCallback(const Grid& grid, const MazeCallback& callback);

    /// @brief Generate a 2D vector representing the maze's grid
    /// @param width Grid width
    /// @param height Grid height
    /// @param defaultValue Default value when allocating grid
    /// @return A 2D vector representing the maze's grid
    inline Grid generateGrid(int width, int height, NodeValue defaultValue = NodeValue::none) { return Grid(height, Directions(width, defaultValue)); }

    /// @brief Get default directions used when generating maze
    /// @return a vector containing { left, right, forward, backward }
    inline Directions getDefaultDirections()
    {
        return Directions
        {
            NodeValue::left, NodeValue::right,
                NodeValue::forward, NodeValue::backward
        };
    }

    constexpr NodeValue flipNodeValue(NodeValue value)
    {
        switch (value)
        {
        case NodeValue::none:
        {
            return NodeValue::none;
        }
        case NodeValue::left:
        {
            return NodeValue::right;
        }
        case NodeValue::right:
        {
            return NodeValue::left;
        }
        case NodeValue::forward:
        {
            return NodeValue::backward;
        }
        case NodeValue::backward:
        {
            return NodeValue::forward;
        }
        case NodeValue::in:
        {
            return NodeValue::in;
        }
        case NodeValue::frontier:
        {
            return NodeValue::frontier;
        }
        default:
        {
            return NodeValue::none;
        }
        }
    }
}

#endif // PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP
