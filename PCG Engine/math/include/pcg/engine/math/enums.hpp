#ifndef PCG_ENGINE_MATH_ENUMS_HPP
#define PCG_ENGINE_MATH_ENUMS_HPP

namespace pcg::engine::math
{
    enum class Axis
    {
        x = 1 << 0,
        y = 1 << 1,
        z = 1 << 2
    };

    enum class Direction
    {
        positive = 0,
        negative = 1
    };

    enum class Plane
    {
        xy = 0,
        xz = 1,
        yz = 2
    };
}

#endif // PCG_ENGINE_MATH_ENUMS_HPP
