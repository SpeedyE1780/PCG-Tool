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

    enum class Axis
    {
        x = 0,
        y = 1,
        z = 2
    };

    enum class Direction
    {
        positive = 0,
        negative = 1
    };

    struct GenerationData
    {
        unsigned int limit;
        float size;
        Vector3 startPoint;
    };

    PCG_ENGINE_CORE_API int add(int x, int y);
    PCG_ENGINE_CORE_API void simpleGeneration(GenerationData* data, Axis axis, Direction direction, addPointCallback callback);
}

#endif // PCG_ENGINE_CORE_CORE_HPP
