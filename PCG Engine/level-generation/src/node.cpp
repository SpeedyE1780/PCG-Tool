#include <pcg/engine/level-generation/node.hpp>

#include <pcg/engine/math/random.hpp>

#include <functional>

namespace pcg::engine::level_generation
{
    Node::Node(const math::Vector3& position) : position(position)
    {
    }

    void Node::addAdjacentNode(utility::enums::Direction direction)
    {
        adjacentNodesDirection |= direction;
        adjacentNodeCount += 1;
    }

    void Node::removeAdjacentNode(utility::enums::Direction direction)
    {
        adjacentNodesDirection &= ~direction;
        adjacentNodeCount -= 1;
    }

    void Node::generateAdjacentNodes(int additionalNodes, const std::vector<utility::enums::Direction>& directions)
    {
        for (utility::enums::Direction direction : directions)
        {
            if (!hasAdjacentNode(direction))
            {
                addAdjacentNode(direction);
                additionalNodes -= 1;

                if (additionalNodes == 0)
                {
                    break;
                }
            }
        }
    }
}
