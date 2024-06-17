#ifndef PCG_ENGINE_UTILITY_ENUMS_HPP
#define PCG_ENGINE_UTILITY_ENUMS_HPP

#include <type_traits>
#include <utility>

namespace pcg::engine::utility::enums
{
    enum class Direction
    {
        left = 1 << 0,
        right = 1 << 1,
        forward = 1 << 2,
        backward = 1 << 3,
        up = 1 << 4,
        down = 1 << 5
    };

    template<typename EnumClass, typename BitOperation>
    EnumClass performBitWiseOperation(EnumClass lhs, EnumClass rhs, BitOperation&& bitOperation)
    {
        static_assert(std::is_enum<EnumClass>::value, "EnumClass must be an enum");
        return static_cast<EnumClass>(bitOperation(std::to_underlying<EnumClass>(lhs), std::to_underlying<EnumClass>(rhs)));
    }
}

#endif // PCG_ENGINE_UTILITY_ENUMS_HPP
