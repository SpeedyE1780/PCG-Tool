#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/math/random.hpp>

#include <algorithm>>
#include <numeric>
#include <random>

namespace pcg::engine::combination_generation
{
    namespace
    {
        int generateCombination(int elementCount)
        {
            const int combinationCount = 1 << elementCount;
            return math::Random::generate(1, combinationCount);
        }

        constexpr bool isElementActive(int index, int combination)
        {
            return ((1 << index) & combination) > 0;
        }

        void toggleElements(int combination, int elementCount, utility::CallbackFunctor<void(int, bool)>&& callback)
        {
            for (int elementIndex = 0; elementIndex < elementCount; ++elementIndex)
            {
                callback(elementIndex, isElementActive(elementIndex, combination));
            }
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
        const int combination = generateCombination(elementCount);
        toggleElements(combination, elementCount, std::move(callback));
    }

    void generateCombination(int elementCount, int minElementCount, utility::CallbackFunctor<void(int, bool)>&& callback)
    {
        int combination = generateCombination(elementCount);
        int activeElements = countActiveBits(combination);

        if (activeElements < minElementCount)
        {
            activateRemainingBits(combination, elementCount, activeElements, minElementCount);
        }

        toggleElements(combination, elementCount, std::move(callback));
    }

    void generateCombination(int elementCount, const std::vector<int>& activeElementIndex, utility::CallbackFunctor<void(int, bool)>&& callback)
    {
        int combination = generateCombination(elementCount);

        for (int elementIndex : activeElementIndex)
        {
            combination |= 1 << elementIndex;
        }

        toggleElements(combination, elementCount, std::move(callback));
    }
}
