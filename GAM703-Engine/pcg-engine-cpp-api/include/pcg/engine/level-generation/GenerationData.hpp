#ifndef PCG_ENGINE_LEVEL_GENERATION_GENERATION_DATA_HPP
#define PCG_ENGINE_LEVEL_GENERATION_GENERATION_DATA_HPP

#include <pcg/engine/math/vector3.hpp>

namespace pcg::engine::level_generation
{
    /// @brief Mode used for Wave Function Collapse
    enum class ExpansionMode
    {
        /// @brief Breadth-First Search
        BFS,
        /// @brief Depth-First Search
        DFS
    };

    /// @brief Data used for level generation
    struct GenerationData
    {
        /// @brief Number of nodes generated
        unsigned int count;
        /// @brief Size of generated node
        float size;
        /// @brief Starting position level is generated
        math::Vector3 startPoint;
    };
}

#endif // PCG_ENGINE_LEVEL_GENERATION_GENERATION_DATA_HPP
