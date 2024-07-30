#ifndef PCG_ENGINE_COMBINATION_GENERATION_COMBINATION_GENERATOR_HPP
#define PCG_ENGINE_COMBINATION_GENERATION_COMBINATION_GENERATOR_HPP

#include <pcg/engine/utility/CallbackFunctor.hpp>

#include <vector>

namespace pcg::engine::combination_generation
{
    /// @brief Generate a combination given a number of elements
    /// @param elementCount Number of element that are available in set
    /// @param callback Callback to add element to generated set
    void generateCombination(int elementCount, utility::CallbackFunctor<void(int, bool)>&& callback);
    /// @brief Generate a combination with at least minimumElementCount elements
    /// @param elementCount Number of element that are available in set
    /// @param minElementCount Minimum number of elements in set
    /// @param callback Callback to add element to generated set
    void generateCombination(int elementCount, int minElementCount, utility::CallbackFunctor<void(int, bool)>&& callback);
    /// @brief Generate a combination with the given elements active
    /// @param elementCount Number of element that are available in set
    /// @param activeElementIndex Vector of elements that must be included
    /// @param callback Callback to add element to generated set
    void generateCombination(int elementCount, const std::vector<int>& activeElementIndex, utility::CallbackFunctor<void(int, bool)>&& callback);
}

#endif // PCG_ENGINE_COMBINATION_GENERATION_COMBINATION_GENERATOR_HPP
