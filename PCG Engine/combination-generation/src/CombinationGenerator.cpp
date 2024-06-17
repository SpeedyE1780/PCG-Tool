#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/math/random.hpp>

#include <algorithm>>
#include <numeric>
#include <random>
#include <vector>

namespace pcg::engine::combination_generation
{
    namespace
    {
        constexpr bool isElementActive(int index, int combination)
        {
            return ((1 << index) & combination) > 0;
        }

        constexpr int countActiveBits(int combination)
        {
            int activeBits = 0;

            for (int tempCombination = combination; tempCombination > 0; tempCombination >>= 1)
            {
                if ((tempCombination & 1) > 0)
                {
                    activeBits += 1;
                }
            }

            return activeBits;
        }

        void activateRemainingBits(int& combination, int elementCount, int activeBits, int minimumBits)
        {
            std::vector<int> indices(elementCount);
            std::default_random_engine randomEngine{};
            std::iota(begin(indices), end(indices), 0);
            std::shuffle(begin(indices), end(indices), randomEngine);

            for (int elementIndex : indices)
            {
                if (isElementActive(elementIndex, combination))
                {
                    continue;
                }

                combination |= 1 << elementIndex;
                activeBits += 1;

                if (activeBits >= minimumBits)
                {
                    break;
                }
            }
        }
    }

    void generateCombination(int elementCount, utility::CallbackFunctor<void(int, bool)>&& callback)
    {
        const int combinationCount = 1 << elementCount;
        const int combination = math::Random::generate(0, combinationCount);

        for (int elementIndex = 0; elementIndex < elementCount; ++elementIndex)
        {
            callback(elementIndex, isElementActive(elementIndex, combination));
        }
    }

    void generateCombination(int elementCount, int minElementCount, utility::CallbackFunctor<void(int, bool)>&& callback)
    {
        const int combinationCount = 1 << elementCount;
        int combination = math::Random::generate(1, combinationCount);

        int activeElements = countActiveBits(combination);

        if (activeElements < minElementCount)
        {
            activateRemainingBits(combination, elementCount, activeElements, minElementCount);
        }

        for (int elementIndex = 0; elementIndex < elementCount; ++elementIndex)
        {
            callback(elementIndex, isElementActive(elementIndex, combination));
        }
    }
}
