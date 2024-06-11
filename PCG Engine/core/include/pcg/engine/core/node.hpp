#ifndef PCG_ENGINE_CORE_NODE_HPP
#define PCG_ENGINE_CORE_NODE_HPP

#include <pcg/engine/math/vector3.hpp>

#include <bitset>

namespace pcg::engine::core
{
    class Neighbors
    {
    public:
        static constexpr int count = 6;
        static constexpr int left = 1 << 0;
        static constexpr int right = 1 << 1;
        static constexpr int forward = 1 << 2;
        static constexpr int backward = 1 << 3;
        static constexpr int up = 1 << 4;
        static constexpr int down = 1 << 5;

        bool hasNeighbor(int neighbor) const;
        void addNeighbor(int neighbor);
        void removeNeighbor(int neighbor);

        static int generateNeighbors();

    private:
        std::bitset<count> neighbors;
    };

    class Node
    {
    public:
        const math::Vector3& getPosition() const { return position; }
        void setPosition(const math::Vector3& position) { this->position = position; }

        Neighbors& getNeighbors() { return neighbors; }
        const Neighbors& getNeighbors() const { return neighbors; }

    private:
        math::Vector3 position;
        Neighbors neighbors;
    };
}

#endif // PCG_ENGINE_CORE_NODE_HPP
