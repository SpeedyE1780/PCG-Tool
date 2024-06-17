#ifndef PCG_ENGINE_COMBINATION_GENERATION_COMBINATION_GENERATOR_HPP
#define PCG_ENGINE_COMBINATION_GENERATION_COMBINATION_GENERATOR_HPP

#include <pcg/engine/utility/CallbackFunctor.hpp>

#include <vector>

namespace pcg::engine::combination_generation
{
    void generateCombination(int elementCount, utility::CallbackFunctor<void(int, bool)>&& callback);
    void generateCombination(int elementCount, int minElementCount, utility::CallbackFunctor<void(int, bool)>&& callback);
    void generateCombination(int elementCount, const std::vector<int>& activeElementIndex, utility::CallbackFunctor<void(int, bool)>&& callback);
}

#endif // PCG_ENGINE_COMBINATION_GENERATION_COMBINATION_GENERATOR_HPP
