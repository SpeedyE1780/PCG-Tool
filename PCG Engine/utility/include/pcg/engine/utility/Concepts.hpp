#ifndef PCG_ENGINE_UTILITY_CONCEPTS_HPP
#define PCG_ENGINE_UTILITY_CONCEPTS_HPP

#include <type_traits>

namespace pcg::engine::utility::concepts
{
    /// @brief Require variadic Ts parameters to be of same type as T
    template <typename T, typename... Ts>
    concept are_same = std::conjunction_v<std::is_same<T, Ts>...>;
}

#endif // PCG_ENGINE_UTILITY_CONCEPTS_HPP
