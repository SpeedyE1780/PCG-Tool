#ifndef PCG_ENGINE_MAZE_SIDEWINDER_HPP
#define PCG_ENGINE_MAZE_SIDEWINDER_HPP

#include <pcg/engine/maze/Common.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>

namespace pcg::engine::maze
{
    void sidewinder(int width, int height, utility::CallbackFunctor<int, int, int>&& callback);
}

#endif // PCG_ENGINE_MAZE_SIDEWINDER_HPP
