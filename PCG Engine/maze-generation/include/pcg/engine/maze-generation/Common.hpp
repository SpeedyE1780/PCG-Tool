#ifndef PCG_ENGINE_MAZE_GENERATION_COMMON_HPP
#define PCG_ENGINE_MAZE_GENERATION_COMMON_HPP

#include <pcg/engine/utility/CallbackFunctor.hpp>

namespace pcg::engine::maze_generation
{
    /// @brief Flags used to determine if node has an adjacent node
    enum class NodeValue
    {
        none = 0,
        left = 1 << 1,
        right = 1 << 2,
        forward = 1 << 3,
        backward = 1 << 4,
        in = 1 << 5,
        frontier = 1 << 6
    };

    /// @brief Callback used to notify a node was spawned/modified
    using MazeCallback = utility::CallbackFunctor<void(int, int, NodeValue)>;
}

#endif // PCG_ENGINE_MAZE_GENERATION_COMMON_HPP
