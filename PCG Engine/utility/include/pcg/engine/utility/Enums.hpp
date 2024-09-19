#ifndef PCG_ENGINE_UTILITY_ENUMS_HPP
#define PCG_ENGINE_UTILITY_ENUMS_HPP

#include <pcg/engine/utility/Concepts.hpp>

#include <type_traits>
#include <utility>

/// @brief Apply ~operator to enum
/// @tparam EnumClass Templated enum
/// @param enumValue Value
/// @return ~value
template<typename EnumClass>
constexpr EnumClass operator~(EnumClass enumValue)
{
    static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
    return static_cast<EnumClass>(~std::to_underlying(enumValue));
}

/// @brief Apply & operator between lhs and rhs
/// @tparam EnumClass Templated enum
/// @param lhs Left hand side value
/// @param rhs Right hand side value
/// @return lhs & rhs
template<typename EnumClass>
constexpr EnumClass operator&(EnumClass lhs, EnumClass rhs) noexcept
{
    static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
    return static_cast<EnumClass>(std::to_underlying(lhs) & std::to_underlying(rhs));
}

/// @brief Apply | operator between lhs and rhs
/// @tparam EnumClass Templated enum
/// @param lhs Left hand side value
/// @param rhs Right hand side value
/// @return lhs | rhs
template<typename EnumClass>
constexpr EnumClass operator|(EnumClass lhs, EnumClass rhs) noexcept
{
    static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
    return static_cast<EnumClass>(std::to_underlying(lhs) | std::to_underlying(rhs));
}

/// @brief Apply ^ operator between lhs and rhs
/// @tparam EnumClass Templated enum
/// @param lhs Left hand side value
/// @param rhs Right hand side value
/// @return lhs ^ rhs
template<typename EnumClass>
constexpr EnumClass operator^(EnumClass lhs, EnumClass rhs) noexcept
{
    static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
    return static_cast<EnumClass>(std::to_underlying(lhs) ^ std::to_underlying(rhs));
}

/// @brief Apply &= operator between lhs and rhs
/// @tparam EnumClass Templated enum
/// @param lhs Left hand side value
/// @param rhs Right hand side value
/// @return lhs &= rhs
template<typename EnumClass>
constexpr EnumClass operator&=(EnumClass& lhs, EnumClass rhs) noexcept
{
    static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
    return lhs = lhs & rhs;
}

/// @brief Apply |= operator between lhs and rhs
/// @tparam EnumClass Templated enum
/// @param lhs Left hand side value
/// @param rhs Right hand side value
/// @return lhs |= rhs
template<typename EnumClass>
constexpr EnumClass operator|=(EnumClass& lhs, EnumClass rhs) noexcept
{
    static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
    return lhs = lhs | rhs;
}

/// @brief Apply ^= operator between lhs and rhs
/// @tparam EnumClass Templated enum
/// @param lhs Left hand side value
/// @param rhs Right hand side value
/// @return lhs ^= rhs
template<typename EnumClass>
constexpr EnumClass operator^=(EnumClass& lhs, EnumClass rhs) noexcept
{
    static_assert(std::is_enum_v<EnumClass>, "EnumClass must be an enum");
    return lhs = lhs ^ rhs;
}

namespace pcg::engine::utility::enums
{
    /// @brief Possible directions from node to adjacent node
    enum class Direction
    {
        none = 0,
        left = 1 << 0,
        right = 1 << 1,
        forward = 1 << 2,
        backward = 1 << 3,
        up = 1 << 4,
        down = 1 << 5,
        portalIn = 1 << 6,
        portalOut = 1 << 7
    };

    /// @brief Get flipped direction of given direction
    /// @param direction Direction that we want to flip
    /// @return The flipped direction
    Direction getFlippedDirection(Direction direction);

    /// @brief Check if given value has flag enabled
    /// @tparam EnumClass Templated enum
    /// @param value Value
    /// @param flag Flag that we're looking for
    /// @return True if value has flag
    template<typename EnumClass>
    constexpr bool hasFlag(EnumClass value, EnumClass flag)
    {
        return std::to_underlying(value & flag) > 0;
    }

    /// @brief Check if given value has flags enabled
    /// @tparam EnumClass Templated enum
    /// @tparam ...EnumFlag List of Templated enum of same type
    /// @param value Value
    /// @param ...flags List of flags that we're looking for
    /// @return true if value has all flags
    template<typename EnumClass, typename ...EnumFlag> requires concepts::are_same<EnumClass, EnumFlag...>
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
