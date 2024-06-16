#ifndef PCG_ENGINE_MATH_RANDOM_HPP
#define PCG_ENGINE_MATH_RANDOM_HPP

#include <pcg/engine/utility/CallbackFunctor.hpp>

namespace pcg::engine::math
{
    struct Random
    {
        static utility::CallbackFunctor<void(unsigned int)> seed;
        static utility::CallbackFunctor<int(int, int)> generate;
    };

    void initializeRandom(utility::CallbackFunctor<void(unsigned int)>&& seed, utility::CallbackFunctor<int(int, int)>&& generate);
}

#endif // PCG_ENGINE_MATH_RANDOM_HPP
