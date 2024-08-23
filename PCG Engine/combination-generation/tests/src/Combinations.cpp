#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/math/Random.hpp>

#include <gtest/gtest.h>

#include <functional>
#include <numeric>

namespace pcg::engine::combination_generation::tests
{
    namespace
    {
        void compareCombinations(const std::vector<int>& combination, const std::vector<int>& expected)
        {
            EXPECT_EQ(combination.size(), expected.size());

            for (int i = 0; i < combination.size(); ++i)
            {
                EXPECT_EQ(combination[i], expected[i]);
            }
        }
    }

    TEST(Combination, SimpleCombination)
    {
        math::Random::resetSeed();
        std::vector<int> elements(10);
        std::iota(begin(elements), end(elements), 1);
        std::vector<int> combination{};
        const std::vector<int> expected = { 1, 2, 3, 6 };
        std::function<void(int, bool)> callback = [&elements, &combination](int index, bool included)
            {
                if (included)
                {
                    combination.emplace_back(elements[index]);
                }
            };

        generateCombination(elements.size(), callback);
        compareCombinations(combination, expected);
    }

    TEST(Combination, CombinationWithMinimum7Elements)
    {
        math::Random::resetSeed();
        std::vector<int> elements(10);
        std::iota(begin(elements), end(elements), 1);
        std::vector<int> combination{};
        const std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 8 };
        std::function<void(int, bool)> callback = [&elements, &combination](int index, bool included)
            {
                if (included)
                {
                    combination.emplace_back(elements[index]);
                }
            };

        generateCombination(elements.size(), 7, callback);
        compareCombinations(combination, expected);
    }

    TEST(Combination, CombinationWith1And3And10Active)
    {
        math::Random::resetSeed();
        std::vector<int> elements(10);
        std::iota(begin(elements), end(elements), 1);
        std::vector<int> combination{};
        const std::vector<int> expected = { 1, 2, 3, 6, 10 };
        std::function<void(int, bool)> callback = [&elements, &combination](int index, bool included)
            {
                if (included)
                {
                    combination.emplace_back(elements[index]);
                }
            };

        generateCombination(elements.size(), { 0, 2, 9 }, callback);
        compareCombinations(combination, expected);
    }

    TEST(Combination, CombinationWithOutOfBoundsIndices)
    {
        math::Random::resetSeed();
        std::vector<int> elements(10);
        std::iota(begin(elements), end(elements), 1);
        std::vector<int> combination{};
        const std::vector<int> expected = { 1, 2, 3, 6, 10 };
        std::function<void(int, bool)> callback = [&elements, &combination](int index, bool included)
            {
                if (included)
                {
                    combination.emplace_back(elements[index]);
                }
            };

        generateCombination(elements.size(), { -1, 0, 2, 9, 11, 13, -2 }, callback);
        compareCombinations(combination, expected);
    }
}
