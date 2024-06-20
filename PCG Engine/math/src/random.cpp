#include <pcg/engine/math/random.hpp>

#include <cstdlib>

namespace pcg::engine::math
{
    namespace
    {
        /// @brief Default number generator using rand()
        /// @param minimum Minimum value
        /// @param maximum Maximum value excluded
        /// @return Value in range [minimum, maximum[
        int defaultNumberGenerator(int minimum, int maximum)
        {
            return rand() % (maximum - minimum) + minimum;
        }

        void defaultInitializeSeed(unsigned int seed)
        {
            Random::seed = seed;
            srand(seed);
        }
    }

    utility::CallbackFunctor<void(unsigned int)> Random::initializeSeed = defaultInitializeSeed;
    utility::CallbackFunctor<int(int, int)> Random::generateNumber = defaultNumberGenerator;
    unsigned int Random::seed = 0;

    void initializeRandom(utility::CallbackFunctor<void(unsigned int)>&& seed, utility::CallbackFunctor<int(int, int)>&& generate)
    {
        Random::initializeSeed = seed ? std::move(seed) : defaultInitializeSeed;
        Random::generateNumber = generate ? std::move(generate) : defaultNumberGenerator;
        //Update new function seed to current seed value
        Random::initializeSeed(Random::seed);
    }
}
