#ifndef PCG_ENGINE_LEVEL_GENERATION_GENERATION_DATA_HPP
#define PCG_ENGINE_LEVEL_GENERATION_GENERATION_DATA_HPP

#include <pcg/engine/math/vector3.hpp>

namespace pcg::engine::level_generation
{
    enum class ExpansionMode
    {
        BFS,
        DFS
    };

    struct GenerationData
    {
        unsigned int limit;
        float size;
        math::Vector3 startPoint;
    };
}

#endif // PCG_ENGINE_LEVEL_GENERATION_GENERATION_DATA_HPP
