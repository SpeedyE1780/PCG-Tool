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
            if (minimum == maximum)
            {
                return minimum;
            }

            return rand() % (maximum - minimum) + minimum;
        }
    }

    utility::CallbackFunctor<void(unsigned int)> Random::initializeSeed = srand;
    utility::CallbackFunctor<int(int, int)> Random::generateNumber = defaultNumberGenerator;
    unsigned int Random::seed = 0;

    void Random::updateSeed(unsigned int newSeed)
    {
        seed = newSeed;
        initializeSeed(newSeed);
    }

    void Random::resetSeed()
    {
        updateSeed(seed);
    }

    void Random::initializeRandom(utility::CallbackFunctor<void(unsigned int)>&& seed, utility::CallbackFunctor<int(int, int)>&& generate)
    {
        initializeSeed = seed ? std::move(seed) : srand;
        generateNumber = generate ? std::move(generate) : defaultNumberGenerator;
        //Update new function seed to current seed value
        initializeSeed(Random::seed);
    }

    std::default_random_engine Random::getDefaultEngine()
    {
        return std::default_random_engine{ seed };
    }
}
