#ifndef PCG_ENGINE_CORE_CORE_HPP
#define PCG_ENGINE_CORE_CORE_HPP

#include <pcg/engine/core/config.hpp>

namespace pcg::engine::core
{
    struct Vector3
    {
        float x;
        float y;
        float z;
    };

    typedef void (*addPointCallback)(Vector3 vector);

    struct GenerationData
    {
        unsigned int limit;
        float size;
        Vector3 startPoint;
    };

    PCG_ENGINE_CORE_API int add(int x, int y);
    PCG_ENGINE_CORE_API void simpleGeneration(GenerationData* data, addPointCallback callback);
}

#endif // PCG_ENGINE_CORE_CORE_HPP
