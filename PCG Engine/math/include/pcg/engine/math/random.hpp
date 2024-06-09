#ifndef PCG_ENGINE_MATH_RANDOM_HPP
#define PCG_ENGINE_MATH_RANDOM_HPP

namespace pcg::engine::math
{
    typedef void (*setSeed)(unsigned int seed);
    typedef int (*generateNumber)();

    struct Random
    {
        static setSeed seed;
        static generateNumber generate;
    };

    void initializeRandom(setSeed seed, generateNumber generate);
}

#endif // PCG_ENGINE_MATH_RANDOM_HPP
