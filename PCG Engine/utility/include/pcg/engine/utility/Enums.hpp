#ifndef PCG_ENGINE_UTILITY_ENUMS_HPP
#define PCG_ENGINE_UTILITY_ENUMS_HPP

#include <functional>
#include <type_traits>
#include <utility>

namespace pcg::engine::utility::enums
{
    enum class Direction
    {
        none = 0,
        left = 1 << 0,
        right = 1 << 1,
        forward = 1 << 2,
        backward = 1 << 3,
        up = 1 << 4,
        down = 1 << 5
    };

    /// @brief Get flipped direction of given direction
    /// @param direction Direction that we want to flip
    /// @return The flipped direction
    Direction getFlippedDirection(Direction direction);

    template<typename EnumClass>
    constexpr EnumClass operator~(EnumClass enumValue)
    {
        static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
        return static_cast<EnumClass>(~std::to_underlying(enumValue));
    }

    template<typename EnumClass>
    constexpr EnumClass operator&(EnumClass lhs, EnumClass rhs) noexcept
    {
        static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
        return static_cast<EnumClass>(std::to_underlying(lhs) & std::to_underlying(rhs));
    }

    template<typename EnumClass>
    constexpr EnumClass operator|(EnumClass lhs, EnumClass rhs) noexcept
    {
        static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
        return static_cast<EnumClass>(std::to_underlying(lhs) | std::to_underlying(rhs));
    }

    template<typename EnumClass>
    constexpr EnumClass operator^(EnumClass lhs, EnumClass rhs) noexcept
    {
        static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
        return static_cast<EnumClass>(std::to_underlying(lhs) ^ std::to_underlying(rhs));
    }

    template<typename EnumClass>
    constexpr EnumClass operator&=(EnumClass& lhs, EnumClass rhs) noexcept
    {
        static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
        return lhs = lhs & rhs;
    }

    template<typename EnumClass>
    constexpr EnumClass operator|=(EnumClass& lhs, EnumClass rhs) noexcept
    {
        static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
        return lhs = lhs | rhs;
    }

    template<typename EnumClass>
    constexpr EnumClass operator^=(EnumClass& lhs, EnumClass rhs) noexcept
    {
        static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
        return lhs = lhs ^ rhs;
    }

    template<typename EnumClass>
    constexpr bool hasFlag(EnumClass value, EnumClass flag)
    {
        return std::to_underlying(value & flag) > 0;
    }

    template <typename T, typename... Ts>
    concept are_same = std::conjunction_v<std::is_same<T, Ts>...>;

    template<typename EnumClass, typename ...EnumFlag> requires are_same<EnumClass, EnumFlag...>
    constexpr bool hasFlag(EnumClass value, EnumFlag... flags)
    {
        bool hasFlags = true;

        for (EnumClass flag : { flags... })
        {
            hasFlags &= hasFlag(value, flag);
        }

        return hasFlags;
    }
}

#endif // PCG_ENGINE_UTILITY_ENUMS_HPP
