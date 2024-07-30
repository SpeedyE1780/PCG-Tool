#ifndef PCG_ENGINE_LEVEL_GENERATION_NODE_HPP
#define PCG_ENGINE_LEVEL_GENERATION_NODE_HPP

#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/Enums.hpp>

#include <vector>

namespace pcg::engine::level_generation
{
    /// @brief Class representing a node in the WFC level
    class Node
    {
    public:
        /// @brief Construct Node with no adjcent nodes
        /// @param position Node position
        Node(const math::Vector3& position);

        /// @brief Get node position
        /// @return Node position
        const math::Vector3& getPosition() const { return position; }
        /// @brief Check if node has an adjacent node following the given direction
        /// @param direction The direction to reach adjacent node
        /// @return True if an adjacent node exists following the direction
        bool hasAdjacentNode(utility::enums::Direction direction) const { return pcg::engine::utility::enums::hasFlag(adjacentNodesDirection, direction); }
        /// @brief Get adjacent nodes bit flag
        /// @return Adjacent nodes bit flag
        utility::enums::Direction getAdjacentNodes() const { return adjacentNodesDirection; }
        /// @brief Get number of adjacent nodes
        /// @return Number of adjacent nodes
        int getAdjacentNodesCount() const { return adjacentNodeCount; }

        /// @brief Add adjacent node following the direction
        /// @param direction Direction to reach adjacent node
        void addAdjacentNode(utility::enums::Direction direction);
        /// @brief Remove adjacent node following the direction
        /// @param direction Direction to reach adjacent node
        void removeAdjacentNode(utility::enums::Direction direction);
        /// @brief Generate adjacent nodes
        /// @param additionalNodes Number of adjacent nodes to spawn
        /// @param directions Possible directions used to reach adjacent nodes
        void generateAdjacentNodes(int additionalNodes, const std::vector<utility::enums::Direction>& directions);

    private:
        /// @brief Position in 3d world
        math::Vector3 position{ 0, 0, 0 };
        /// @brief Bit flag representing valid directions to reach adjacent nodes
        utility::enums::Direction adjacentNodesDirection = utility::enums::Direction::none;
        /// @brief Number of adjacent nodes
        int adjacentNodeCount = 0;
    };
}

#endif // PCG_ENGINE_LEVEL_GENERATION_NODE_HPP
