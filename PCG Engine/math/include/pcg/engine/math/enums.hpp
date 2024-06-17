#ifndef PCG_ENGINE_MATH_ENUMS_HPP
#define PCG_ENGINE_MATH_ENUMS_HPP

namespace pcg::engine::math
{
    enum class Axis
    {
        none = 0,
        x = 1 << 0,
        y = 1 << 1,
        z = 1 << 2,
        xy = x | y,
        xz = x | z,
        yz = y | z,
        xyz = x | y | z
    };

    enum class Direction
    {
        positive = 0,
        negative = 1
    };
}

#endif // PCG_ENGINE_MATH_ENUMS_HPP
