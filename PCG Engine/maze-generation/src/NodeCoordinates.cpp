#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/maze-generation/NodeCoordinates.hpp>

namespace pcg::engine::maze_generation
{
    namespace
    {
        /// @brief Return Vector3 used to reach adjacent node following the direction
        /// @param direction Direction from current to adjacent node
        /// @return Vector3 to reach adjacent node
        const math::Vector3& getDirectionVector(NodeValue direction)
        {
            switch (direction)
            {
            case NodeValue::left:
            {
                return math::Vector3::left;
            }
            case NodeValue::right:
            {
                return math::Vector3::right;
            }
            case NodeValue::forward:
            {
                return math::Vector3::forward;
            }
            case NodeValue::backward:
            {
                return math::Vector3::backward;
            }
            default:
            {
                return math::Vector3::zero;
            }
            }
        }
    }

    NodeCoordinates getAdjacentCoordinates(const NodeCoordinates& nodeCoordinates, NodeValue direction)
    {
        auto [adjacentX, adjacentY] = getAdjacentCoordinates(nodeCoordinates.x, nodeCoordinates.y, direction);
        return NodeCoordinates{ adjacentX, adjacentY };
    }

    std::tuple<int, int> getAdjacentCoordinates(int x, int y, NodeValue direction)
    {
        const math::Vector3& directionVector = getDirectionVector(direction);
        const int adjacentX = x + directionVector.x;
        const int adjacentY = y + directionVector.z;
        return std::make_tuple(adjacentX, adjacentY);
    }
}
