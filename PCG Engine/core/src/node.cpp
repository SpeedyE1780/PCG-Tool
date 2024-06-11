#include <pcg/engine/core/node.hpp>

#include <pcg/engine/math/random.hpp>

namespace pcg::engine::core
{
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

    int Neighbors::generateNeighbors()
    {
        return math::Random::generate(0, count);
    }
}
