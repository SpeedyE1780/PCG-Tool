#ifndef PCG_ENGINE_MAZE_GENERATION_NODE_COORDINATES_HPP
#define PCG_ENGINE_MAZE_GENERATION_NODE_COORDINATES_HPP

#include <pcg/engine/maze-generation/Common.hpp>

#include <functional>
#include <tuple>

namespace pcg::engine::maze_generation
{
    /// @brief POD class containing Node x y coordinates
    struct NodeCoordinates
    {
        int x;
        int y;
    };

    inline bool operator==(const NodeCoordinates& lhs, const NodeCoordinates& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }

    /// @brief Get adjacent node x, y coordinates
    /// @param nodeCoordinates Current node coordinates
    /// @param direction Direction from current node to adjacent node
    /// @return NodeCoordinates containing adjacent node x, y coordinate
    NodeCoordinates getAdjacentCoordinates(const NodeCoordinates& nodeCoordinates, NodeValue direction);
    /// @brief Get adjacent node x, y coordinates
    /// @param x Current node x coordinate
    /// @param y Current node y coordinate
    /// @param direction Direction from current node to adjacent node
    /// @return tuple containing adjacent node x, y coordinate
    std::tuple<int, int> getAdjacentCoordinates(int x, int y, NodeValue direction);
}

namespace std
{
    template<>
    struct hash<pcg::engine::maze_generation::NodeCoordinates>
    {
        std::size_t operator()(const pcg::engine::maze_generation::NodeCoordinates& nodeCoordinates) const
        {
            std::size_t x = std::hash<int>{}(nodeCoordinates.x);
            std::size_t y = std::hash<int>{}(nodeCoordinates.y);

            return x ^ (y << 1);
        }
    };
}

#endif // PCG_ENGINE_MAZE_GENERATION_NODE_COORDINATES_HPP
