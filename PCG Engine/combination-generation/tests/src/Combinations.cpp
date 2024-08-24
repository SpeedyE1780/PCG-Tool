#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/math/Random.hpp>

#include <pcg/engine/tests/PCGTest.hpp>

#include <gtest/gtest.h>

#include <functional>
#include <numeric>

using PCGTest = pcg::engine::tests::PCGTest;

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

        class Combination : public PCGTest
        {
        protected:
            virtual void SetUp() override
            {
                PCGTest::SetUp();
                std::iota(begin(elements), end(elements), 1);
            }

            std::vector<int> elements = std::vector<int>(10);
            std::vector<int> combination{};
        };
    }

    TEST_F(Combination, SimpleCombination)
    {
        const std::vector<int> expected = { 1, 2, 3, 6 };

        generateCombination(elements.size(), [this](int index, bool included)
            {
                if (included)
                {
                    combination.emplace_back(elements[index]);
                }
            });
        compareCombinations(combination, expected);
    }

    TEST_F(Combination, CombinationWithMinimum7Elements)
    {
        const std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 8 };

        generateCombination(elements.size(), 7, [this](int index, bool included)
            {
                if (included)
                {
                    combination.emplace_back(elements[index]);
                }
            });
        compareCombinations(combination, expected);
    }

    TEST_F(Combination, CombinationWith1And3And10Active)
    {
        const std::vector<int> expected = { 1, 2, 3, 6, 10 };

        generateCombination(elements.size(), { 0, 2, 9 }, [this](int index, bool included)
            {
                if (included)
                {
                    combination.emplace_back(elements[index]);
                }
            });
        compareCombinations(combination, expected);
    }

    TEST_F(Combination, CombinationWithOutOfBoundsIndices)
    {
        const std::vector<int> expected = { 1, 2, 3, 6, 10 };

        generateCombination(elements.size(), { -1, 0, 2, 9, 11, 13, -2 }, [this](int index, bool included)
            {
                if (included)
                {
                    combination.emplace_back(elements[index]);
                }
            });
        compareCombinations(combination, expected);
    }
}
