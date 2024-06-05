#ifndef PCG_ENGINE_CORE_CORE_HPP
#define PCG_ENGINE_CORE_CORE_HPP

#include <pcg/engine/core/config.hpp>

namespace pcg::engine::core
{
    typedef void (*addPointCallback)(float x, float y, float z);

    PCG_ENGINE_CORE_API int add(int x, int y);
    PCG_ENGINE_CORE_API void simpleGeneration(addPointCallback callback);
}

#endif // PCG_ENGINE_CORE_CORE_HPP
