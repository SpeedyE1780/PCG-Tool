#ifndef PCG_ENGINE_CORE_GENERATION_DATA_HPP
#define PCG_ENGINE_CORE_GENERATION_DATA_HPP

#include <pcg/engine/math/vector3.hpp>

namespace pcg::engine::core
{
    typedef void (*addPointCallback)(math::Vector3 vector);
    typedef void (*addWFCPointCallback)(math::Vector3 vector, int neighbors);

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

#endif // PCG_ENGINE_CORE_GENERATION_DATA_HPP
