#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/math/random.hpp>

#include <algorithm>
#include <numeric>
#include <random>

namespace pcg::engine::combination_generation
{
    namespace
    {
        /// @brief Generate a combination based on the number of elements in the set
        /// @param elementCount Number of elements in set
        /// @return The selected combination
        int generateCombination(int elementCount)
        {
            const int combinationCount = 1 << elementCount;
            return math::Random::number(1, combinationCount);
        }

        /// @brief Check if an element is in the generated combination
        /// @param index Index of element in set
        /// @param combination Generated combination
        /// @return True if element is in generated combination
        constexpr bool isElementActive(int index, int combination)
        {
            return ((1 << index) & combination) > 0;
        }

        /// @brief Loops through each element in set and notifies game engine of element status (Included/Not Included in set)
        /// @param combination Generated combination
        /// @param elementCount Number of element in set
        /// @param callback Callback notifying game engine if current element is in set
        void toggleElements(int combination, int elementCount, utility::CallbackFunctor<void(int, bool)>&& callback)
        {
            for (int elementIndex = 0; elementIndex < elementCount; ++elementIndex)
            {
                callback(elementIndex, isElementActive(elementIndex, combination));
            }
        }

        /// @brief Checks number of active elements in combination
        /// @param combination Generated combination
        /// @return Number of active elements in combination
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

        /// @brief Activate elements in combination until the minimum active element count is reached
        /// @param combination Generated combination that will be modified during call
        /// @param elementCount Number of elements in set
        /// @param activeBits Current number of active elements
        /// @param minimumBits Minimum number of active elements
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
        std::for_each(begin(activeElementIndex), end(activeElementIndex),
            [&combination, elementCount](int elementIndex)
            {
                if (elementIndex >= 0 && elementIndex < elementCount)
                {
                    combination |= 1 << elementIndex;
                }
            });

        toggleElements(combination, elementCount, std::move(callback));
    }
}
