#ifndef PCG_ENGINE_CORE_CORE_HPP
#define PCG_ENGINE_CORE_CORE_HPP

#include <pcg/engine/core/config.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::core
{
    typedef void (*addPointCallback)(math::Vector3 vector);
    typedef void (*addWFCPointCallback)(math::Vector3 vector, int neighbors);

    struct GenerationData
    {
        unsigned int limit;
        float size;
        math::Vector3 startPoint;
    };

    enum class ExpansionMode
    {
        BFS,
        DFS
    };
}

#endif // PCG_ENGINE_CORE_CORE_HPP
