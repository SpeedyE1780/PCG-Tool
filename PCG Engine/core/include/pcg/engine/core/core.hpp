#ifndef PCG_ENGINE_CORE_CORE_HPP
#define PCG_ENGINE_CORE_CORE_HPP

#include <pcg/engine/core/config.hpp>

#include <functional>

namespace pcg::engine::core
{
    PCG_ENGINE_CORE_API int add(int x, int y);
    PCG_ENGINE_CORE_API void simpleGeneration(std::function<void(float, float, float)> callback);
}

#endif // PCG_ENGINE_CORE_CORE_HPP
