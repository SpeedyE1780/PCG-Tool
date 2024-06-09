#include <pcg/engine/math/random.hpp>

#include <cstdlib>

namespace pcg::engine::math
{
    setSeed Random::seed = srand;
    generateNumber Random::generate = rand;

    void initializeRandom(setSeed seed, generateNumber generate)
    {
        Random::seed = seed;
        Random::generate = generate;
    }
}
