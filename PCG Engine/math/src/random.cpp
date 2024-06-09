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

    setSeed Random::seed = srand;
    generateNumber Random::generate = defaultNumberGenerator;

    void initializeRandom(setSeed seed, generateNumber generate)
    {
        Random::seed = seed ? seed : srand;
        Random::generate = generate ? generate : defaultNumberGenerator;
    }
}
