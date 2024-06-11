#ifndef PCG_ENGINE_CORE_WAVE_FUNCTION_COLLAPSE_HPP
#define PCG_ENGINE_CORE_WAVE_FUNCTION_COLLAPSE_HPP

#include <pcg/engine/core/GenerationData.hpp>

#include <pcg/engine/math/vector3.hpp>

namespace pcg::engine::core
{
    typedef void (*addWFCPointCallback)(math::Vector3 vector, int neighbors);

    enum class ExpansionMode
    {
        BFS,
        DFS
    };

    void waveFunctionCollapse(GenerationData* data, ExpansionMode mode, addWFCPointCallback callback);
}

#endif // PCG_ENGINE_CORE_WAVE_FUNCTION_COLLAPSE_HPP
