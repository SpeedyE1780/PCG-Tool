#ifndef PCG_ENGINE_MAZE_GENERATION_COMMON_HPP
#define PCG_ENGINE_MAZE_GENERATION_COMMON_HPP

#include <pcg/engine/utility/Enums.hpp>

#include <functional>

namespace pcg::engine::maze_generation
{
    /// @brief Flags used to determine if node has an adjacent node
    enum class NodeValue
    {
        none = 0,
        left = 1 << 0,
        right = 1 << 1,
        forward = 1 << 2,
        backward = 1 << 3,
        in = 1 << 4,
        frontier = 1 << 5,
        allDirections = left | right | forward | backward
    };

    /// @brief Callback used to notify a node was spawned/modified
    using MazeCallback = std::function<void(int, int, NodeValue)>;
}

#endif // PCG_ENGINE_MAZE_GENERATION_COMMON_HPP
