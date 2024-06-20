#ifndef PCG_ENGINE_MATH_ENUMS_HPP
#define PCG_ENGINE_MATH_ENUMS_HPP

namespace pcg::engine::math
{
    /// @brief Axis bitflag indicating which axes are enabled
    enum class Axis
    {
        none = 0,
        positiveX = 1 << 0,
        negativeX = 1 << 1,
        positiveY = 1 << 2,
        negativeY = 1 << 3,
        positiveZ = 1 << 4,
        negativeZ = 1 << 5,
        x = positiveX | negativeX,
        y = positiveY | negativeY,
        z = positiveZ | negativeZ,
        xy = x | y,
        xz = x | z,
        yz = y | z,
        xyz = x | y | z
    };
}

#endif // PCG_ENGINE_MATH_ENUMS_HPP
