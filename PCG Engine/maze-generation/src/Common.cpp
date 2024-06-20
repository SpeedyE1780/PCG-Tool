#ifndef PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
#define PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP

#include <pcg/engine/maze-generation/Common.hpp>

#include <pcg/engine/math/vector3.hpp>

namespace pcg::engine::maze_generation
{
    std::tuple<int, int> getAdjacentCoordinates(int x, int y, utility::enums::Direction direction)
    {
        const math::Vector3& directionVector = math::getUnitVectorFromDirection(direction);
        int nx = x + directionVector.x;
        int ny = y + directionVector.z;
        return { nx, ny };
    }
}

#endif // PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
