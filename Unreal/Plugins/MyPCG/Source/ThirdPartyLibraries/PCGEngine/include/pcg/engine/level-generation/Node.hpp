#ifndef PCG_ENGINE_LEVEL_GENERATION_NODE_HPP
#define PCG_ENGINE_LEVEL_GENERATION_NODE_HPP

#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/Enums.hpp>

#include <vector>

namespace pcg::engine::level_generation
{
    /// @brief Class representing a node in the WFC level
    template<typename Vector>
    class Node
    {
    public:
        /// @brief Construct Node with no adjcent nodes
        /// @param position Node position
        Node(const Vector& position) : position(position)
        {
        }

        /// @brief Get node position
        /// @return Node position
        const Vector& getPosition() const { return position; }
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
        void addAdjacentNode(utility::enums::Direction direction)
        {
            adjacentNodesDirection |= direction;
            adjacentNodeCount += 1;
        }

        /// @brief Remove adjacent node following the direction
        /// @param direction Direction to reach adjacent node
        void removeAdjacentNode(utility::enums::Direction direction)
        {
            adjacentNodesDirection &= ~direction;
            adjacentNodeCount -= 1;
        }

        /// @brief Generate adjacent nodes
        /// @param additionalNodes Number of adjacent nodes to spawn
        /// @param directions Possible directions used to reach adjacent nodes
        void generateAdjacentNodes(int additionalNodes, const std::vector<utility::enums::Direction>& directions)
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

    private:
        /// @brief Position in 3d world
        Vector position{};
        /// @brief Bit flag representing valid directions to reach adjacent nodes
        utility::enums::Direction adjacentNodesDirection = utility::enums::Direction::none;
        /// @brief Number of adjacent nodes
        int adjacentNodeCount = 0;
    };
}

#endif // PCG_ENGINE_LEVEL_GENERATION_NODE_HPP
