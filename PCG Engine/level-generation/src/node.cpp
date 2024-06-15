#include <pcg/engine/level-generation/node.hpp>

#include <pcg/engine/math/random.hpp>

namespace pcg::engine::level_generation
{
    Node::Node(const math::Vector3& position) :position(position), neighbors()
    {
    }

    int Neighbors::getIntegerRepresentation() const
    {
        return neighbors.to_ulong();
    }

    int Neighbors::getNeighborCount() const
    {
        return neighbors.count();
    }

    bool Neighbors::hasNeighbor(int neighbor) const
    {
        return (neighbors & std::bitset<count>(neighbor)).any();
    }

    void Neighbors::addNeighbor(int neighbor)
    {
        neighbors |= neighbor;
    }

    void Neighbors::removeNeighbor(int neighbor)
    {
        neighbors &= ~neighbor;
    }

    void Neighbors::generateNeighbors(int additionalNeighbor, std::vector<int>&& directions)
    {
        for (int direction : directions)
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
