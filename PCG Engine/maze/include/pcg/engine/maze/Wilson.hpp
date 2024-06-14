#ifndef PCG_ENGINE_MAZE_WILSON_HPP
#define PCG_ENGINE_MAZE_WILSON_HPP

#include <pcg/engine/maze/Common.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>

namespace pcg::engine::maze
{
    void wilson(int width, int height, utility::CallbackFunctor<int, int, int> callback);
}

#endif // PCG_ENGINE_MAZE_WILSON_HPP
