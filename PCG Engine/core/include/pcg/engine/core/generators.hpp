#ifndef PCG_ENGINE_CORE_CORE_HPP
#define PCG_ENGINE_CORE_CORE_HPP

#include <pcg/engine/math/vector3.hpp>

namespace pcg::engine::core
{
    typedef void (*addWFCPointCallback)(math::Vector3 vector, int neighbors);

    enum class ExpansionMode
    {
        BFS,
        DFS
    };
}

#endif // PCG_ENGINE_CORE_CORE_HPP
