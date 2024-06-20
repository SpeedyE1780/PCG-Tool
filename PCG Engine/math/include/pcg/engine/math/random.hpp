#ifndef PCG_ENGINE_MATH_RANDOM_HPP
#define PCG_ENGINE_MATH_RANDOM_HPP

#include <pcg/engine/utility/CallbackFunctor.hpp>

namespace pcg::engine::math
{
    /// @brief Random class is in charge of Random Number Generation (RNG)
    struct Random
    {
        /// @brief Set functions used to intialize seed and generate numbers
        /// @param seed Function that will intialize the RNG seed
        /// @param generate Function used to generate numbers
        static void initializeRandom(utility::CallbackFunctor<void(unsigned int)>&& seed, utility::CallbackFunctor<int(int, int)>&& generate);

        /// @brief Call initialize seed and update the stored seed value
        /// @param newSeed The new RNG seed
        static void updateSeed(unsigned int newSeed);

        /// @brief Function used to generate a number between [min, max[
        static utility::CallbackFunctor<int(int, int)> generateNumber;
        /// @brief Current RNG seed
        static unsigned int seed;

    private:
        /// @brief Function used to set the RNG seed
        static utility::CallbackFunctor<void(unsigned int)> initializeSeed;
    };
}

#endif // PCG_ENGINE_MATH_RANDOM_HPP
