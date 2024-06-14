#ifndef PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
#define PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP

#include <pcg/engine/utility/CallbackFunctor.hpp>

namespace pcg::engine::maze
{
    void aldousBroder(int width, int height, utility::CallbackFunctor<int, int, int>&& callback);
}

#endif // PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
