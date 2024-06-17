#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/math/random.hpp>

namespace pcg::engine::combination_generation
{
    void generateCombination(int elementCount, utility::CallbackFunctor<void(int, bool)>&& callback)
    {
        const int combinationCount = 1 << elementCount;
        const int combination = math::Random::generate(0, combinationCount);

        for (int elementIndex = 0; elementIndex < elementCount; ++elementIndex)
        {
            callback(elementIndex, ((1 << elementIndex) & combination) > 0);
        }
    }
}
