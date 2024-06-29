#ifndef PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP
#define PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP

#include <pcg/engine/maze-generation/Common.hpp>

#include <vector>

namespace pcg::engine::maze_generation
{
    /// @brief Direction vector alias
    using Directions = std::vector<NodeValue>;
    /// @brief 2D vector alias
    using Grid = std::vector<Directions>;

    /// @brief Invoke callback on a single node
    /// @param x X coordinate in grid
    /// @param y Y coordinate in grid
    /// @param grid Grid representing maze
    /// @param callback User defined callback
    inline void invokeNodeCallback(int x, int y, const Grid& grid, const MazeCallback& callback);
    /// @brief Invoke callback on a pair of adjacent node
    /// @param x X coordinate in grid
    /// @param y Y coordinate in grid
    /// @param adjacentX adjacent X coordinate in grid
    /// @param adjacentY adjacent Y coordinate in grid
    /// @param grid Grid representing maze
    /// @param callback User defined callback
    inline void invokeNodePairCallback(int x, int y, int adjacentX, int adjacentY, const Grid& grid, const MazeCallback& callback);
    /// @brief Loops over grid and invoke callback on each node
    /// @param grid Grid representing maze
    /// @param callback User defined callback
    inline void invokeCallback(const Grid& grid, const MazeCallback& callback);

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

    /// @brief Check that value is within index range [0, size[
    /// @param index Index that is being checked
    /// @param size Collection size
    /// @return True is index is within range [0, size[
    constexpr bool isWithinBounds(int index, int size) { return index >= 0 && index < size; }
    /// @brief Checks that x y are within the Grid's bound x within [0, width[ y within [0, height[
    /// @param x x index
    /// @param y y index
    /// @param width Grid width
    /// @param height Grid height
    /// @return True if x is within [0, width[ & y is within [0, height[
    constexpr bool isWithinGridBounds(int x, int y, int width, int height) { return isWithinBounds(x, width) && isWithinBounds(y, height); }

    /// @brief Adds a path between the node and adjacent node following the given direction
    /// @param nodeX Node X coordinate
    /// @param nodeY Node Y coordinate
    /// @param adjacentNodeX Adjacent Node X coordinate
    /// @param adjacentNodeY Adjacent Node Y coordinate
    /// @param direction Path direction from node to adjacent
    /// @param grid Grid representing maze
    void addAdjacentNodePath(int nodeX, int nodeY, int adjacentNodeX, int adjacentNodeY, NodeValue direction, Grid& grid);
    /// @brief Adds a wall between the node and adjacent node following the given direction
    /// @param nodeX Node X coordinate
    /// @param nodeY Node Y coordinate
    /// @param adjacentNodeX Adjacent Node X coordinate
    /// @param adjacentNodeY Adjacent Node Y coordinate
    /// @param direction wall direction from node to adjacent
    /// @param grid Grid representing maze
    void addAdjacentNodeWall(int nodeX, int nodeY, int adjacentNodeX, int adjacentNodeY, NodeValue direction, Grid& grid);
    /// @brief Add Outer edges wall to grid
    /// @param grid Grid representing maze
    /// @param width Grid Width
    /// @param height Grid Height
    void addGridBounds(Grid& grid, int width, int height);
}

#endif // PCG_ENGINE_MAZE_GENERATION_UTILITY_HPP
