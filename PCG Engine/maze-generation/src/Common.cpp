#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/maze-generation/Common.hpp>

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
