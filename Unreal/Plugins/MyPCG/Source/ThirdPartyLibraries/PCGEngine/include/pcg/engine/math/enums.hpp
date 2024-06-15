#ifndef PCG_ENGINE_MATH_ENUMS_HPP
#define PCG_ENGINE_MATH_ENUMS_HPP

namespace pcg::engine::math
{
    namespace axis
    {
        using Flag = int;

        constexpr Flag x = 1 << 0;
        constexpr Flag y = 1 << 1;
        constexpr Flag z = 1 << 2;
        constexpr Flag xy = x | y;
        constexpr Flag xz = x | z;
        constexpr Flag yz = y | z;
        constexpr Flag xyz = x | y | z;
    }

    enum class Direction
    {
        positive = 0,
        negative = 1
    };
}

#endif // PCG_ENGINE_MATH_ENUMS_HPP
