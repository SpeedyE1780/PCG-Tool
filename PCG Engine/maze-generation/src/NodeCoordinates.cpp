#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/maze-generation/NodeCoordinates.hpp>

namespace pcg::engine::maze_generation
{
    NodeCoordinates getAdjacentCoordinates(const NodeCoordinates& nodeCoordinates, utility::enums::Direction direction)
    {
        const math::Vector3& directionVector = math::getUnitVectorFromDirection(direction);
        const int x = nodeCoordinates.x + directionVector.x;
        const int y = nodeCoordinates.y + directionVector.z;
        return NodeCoordinates{ x, y };
    }
}
