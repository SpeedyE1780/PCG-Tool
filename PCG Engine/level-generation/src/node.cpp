#include <pcg/engine/level-generation/node.hpp>

#include <pcg/engine/math/random.hpp>

#include <functional>

namespace pcg::engine::level_generation
{
    Node::Node(const math::Vector3& position) : position(position), neighbors()
    {
    }

    void Neighbors::addNeighbor(utility::enums::Direction neighbor)
    {
        neighbors |= neighbor;
        neighborCount += 1;
    }

    void Neighbors::removeNeighbor(utility::enums::Direction neighbor)
    {
        neighbors &= ~neighbor;
        neighborCount -= 1;
    }

    void Neighbors::generateNeighbors(int additionalNeighbor, std::vector<utility::enums::Direction>&& directions)
    {
        for (utility::enums::Direction direction : directions)
        {
            if (!hasNeighbor(direction))
            {
                addNeighbor(direction);
                additionalNeighbor -= 1;

                if (additionalNeighbor == 0)
                {
                    break;
                }
            }
        }
    }
}
