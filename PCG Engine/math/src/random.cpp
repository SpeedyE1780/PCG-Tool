#include <pcg/engine/math/random.hpp>

#include <cstdlib>

namespace pcg::engine::math
{
    namespace
    {
        int defaultNumberGenerator(int minimum, int maximum)
        {
            return rand() % (maximum - minimum) + minimum;
        }
    }

    utility::CallbackFunctor<void(unsigned int)> Random::seed = srand;
    utility::CallbackFunctor<int(int, int)> Random::generate = defaultNumberGenerator;

    void initializeRandom(utility::CallbackFunctor<void(unsigned int)>&& seed, utility::CallbackFunctor<int(int, int)>&& generate)
    {
        Random::seed = seed ? std::move(seed) : srand;
        Random::generate = generate ? std::move(generate) : defaultNumberGenerator;
    }
}
