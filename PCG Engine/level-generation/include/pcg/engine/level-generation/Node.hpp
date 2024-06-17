#ifndef PCG_ENGINE_LEVEL_GENERATION_NODE_HPP
#define PCG_ENGINE_LEVEL_GENERATION_NODE_HPP

#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/Enums.hpp>

#include <vector>

namespace pcg::engine::level_generation
{
    class Neighbors
    {
    public:
        void addNeighbor(utility::enums::Direction neighbor);
        void removeNeighbor(utility::enums::Direction neighbor);
        bool hasNeighbor(utility::enums::Direction neighbor) const { return pcg::engine::utility::enums::hasFlag(neighbors, neighbor); }
        utility::enums::Direction getNeighbors() const { return neighbors; }
        int getNeighborCount() const { return neighborCount; }

        void generateNeighbors(int additionalNeighbor, std::vector<utility::enums::Direction>&& directions);

    private:
        utility::enums::Direction neighbors = utility::enums::Direction::none;
        int neighborCount = 0;
    };

    class Node
    {
    public:
        Node(const math::Vector3& position);
        const math::Vector3& getPosition() const { return position; }
        void setPosition(const math::Vector3& position) { this->position = position; }

        Neighbors& getNeighbors() { return neighbors; }
        const Neighbors& getNeighbors() const { return neighbors; }

    private:
        math::Vector3 position;
        Neighbors neighbors;
    };
}

#endif // PCG_ENGINE_LEVEL_GENERATION_NODE_HPP
