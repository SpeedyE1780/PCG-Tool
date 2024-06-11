#include <pcg/engine/core/node.hpp>

#include <pcg/engine/math/random.hpp>

namespace pcg::engine::core
{
    Node::Node(const math::Vector3& position) :position(position), neighbors()
    {
    }

    int Neighbors::getIntegerRepresentation() const
    {
        return neighbors.to_ulong();
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

    void Neighbors::generateNeighbors()
    {
        neighbors |= math::Random::generate(0, combinationCount);
    }
}
