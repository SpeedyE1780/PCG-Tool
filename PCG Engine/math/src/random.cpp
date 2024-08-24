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

    std::function<void(unsigned int)> Random::initializeSeed = srand;
    std::function<int(int, int)> Random::generateNumber = defaultNumberGenerator;
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

    void Random::initializeRandom(const std::function<void(unsigned int)>& seed, const std::function<int(int, int)>& generate)
    {
        initializeSeed = seed ? seed : srand;
        generateNumber = generate ? generate : defaultNumberGenerator;
        //Update new function seed to current seed value
        initializeSeed(Random::seed);
    }

    std::default_random_engine Random::getDefaultEngine()
    {
        return std::default_random_engine{ seed };
    }
}
