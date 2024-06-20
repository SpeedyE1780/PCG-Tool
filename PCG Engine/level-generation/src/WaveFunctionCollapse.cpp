#include <pcg/engine/level-generation/Node.hpp>
#include <pcg/engine/level-generation/WaveFunctionCollapse.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <optional>
#include <queue>
#include <random>
#include <sstream>
#include <stack>

namespace pcg::engine::level_generation
{
    namespace
    {
        using NodeVector = std::vector <Node>;

        /// @brief Get directions from chosen axes
        /// @param axes Axes that will be used to generate level
        /// @return Vector containing all directions used
        std::vector<utility::enums::Direction> getDirections(math::Axis axes)
        {
            std::vector<utility::enums::Direction> directions{};

            if (utility::enums::hasFlag(axes, math::Axis::positiveX))
            {
                directions.emplace_back(utility::enums::Direction::right);
            }

            if (utility::enums::hasFlag(axes, math::Axis::negativeX))
            {
                directions.emplace_back(utility::enums::Direction::left);
            }

            if (utility::enums::hasFlag(axes, math::Axis::positiveY))
            {
                directions.emplace_back(utility::enums::Direction::up);
            }

            if (utility::enums::hasFlag(axes, math::Axis::negativeY))
            {
                directions.emplace_back(utility::enums::Direction::down);
            }

            if (utility::enums::hasFlag(axes, math::Axis::positiveZ))
            {
                directions.emplace_back(utility::enums::Direction::forward);
            }

            if (utility::enums::hasFlag(axes, math::Axis::negativeZ))
            {
                directions.emplace_back(utility::enums::Direction::backward);
            }

            return directions;
        }

        /// @brief Spawns new node if it wasn't already spawned
        /// @tparam NodeCollection Collection of pending nodes (stack or queue)
        /// @param pendingNodes Pending nodes that haven't been processed yet
        /// @param spawnedNodes Vector of nodes that are spawned
        /// @param position Node position
        /// @return An iterator to the existing node in the spawnedNodes or an std::nullopt if the node wasn't previously spawned
        template<typename NodeCollection>
        std::optional<NodeVector::iterator> spawnNode(NodeCollection& pendingNodes, NodeVector& spawnedNodes, const math::Vector3& position)
        {
            std::ostringstream oss{};

            oss << "Node: " << position.x << " " << position.y << " " << position.z << " ";
            auto node = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&position](const Node& node)
                {
                    return node.getPosition() == position;
                });

            if (node == end(spawnedNodes))
            {
                pendingNodes.push(spawnedNodes.size());
                spawnedNodes.emplace_back(Node(position));
                oss << "added";
                utility::logInfo(oss.str());
                return std::nullopt;
            }

            oss << "already addded";
            utility::logWarning(oss.str());
            return node;
        }

        /// @brief Get next element in queue
        /// @tparam T Type of elements in queue
        /// @param queue Queue of T
        /// @return The element at the front of the queue
        template<typename T>
        const T& getNext(const std::queue<T>& queue)
        {
            return queue.front();
        }

        /// @brief Get next element in stack
        /// @tparam T Type of elements in stack
        /// @param stack Stack of T
        /// @return The element at the top of the stack
        template<typename T>
        const T& getNext(const std::stack<T>& stack)
        {
            return stack.top();
        }

        /// @brief Get position of adjacent node following the direction
        /// @param currentPosition Position of current node
        /// @param direction Direction to reach adjacent node
        /// @param size The size of the nodes
        /// @return Adjacent node position
        math::Vector3 getAdjacentNodePosition(const math::Vector3& currentPosition, utility::enums::Direction direction, float size)
        {
            return currentPosition + math::getUnitVectorFromDirection(direction) * size;
        }

        /// @brief Class representing current wave function collapse data
        /// @tparam NodeCollection Collection of pending nodes (stack or queue)
        template<typename NodeCollection>
        class WaveFunctionCollapseData
        {
        public:
            /// @brief Initialize Data
            /// @param pendingNodes Current pending nodes collection
            /// @param spawnedNodes Current spawned nodes vector
            /// @param currentIndex Index of node being processed
            /// @param size Size of each node
            WaveFunctionCollapseData(NodeCollection& pendingNodes, NodeVector& spawnedNodes, std::size_t currentIndex, float size) :
                pendingNodes(pendingNodes),
                spawnedNodes(spawnedNodes),
                currentIndex(currentIndex),
                nodeSize(size)
            {
            }

            /// @brief Get node being currently processed
            /// @return Node being currently processed
            Node& getCurrentNode() { return spawnedNodes.at(currentIndex); }
            /// @brief Get node being currently processed
            /// @return Node being currently processed
            const Node& getCurrentNode() const { return spawnedNodes.at(currentIndex); }
            /// @brief Get last spawned node
            /// @return Last spawned node
            Node& getLastSpawnedNode() { return spawnedNodes.back(); }
            /// @brief Get last spawned node
            /// @return Last spawned node
            const Node& getLastSpawnedNode() const { return spawnedNodes.back(); }
            /// @brief Get the size of each node
            /// @return The size of each node
            float getNodeSize() const { return nodeSize; }
            /// @brief Get collection of nodes not processed yet
            /// @return Collection of nodes not processed yet
            NodeCollection& getPendingNodes() { return pendingNodes; }
            /// @brief Get collection of nodes not processed yet
            /// @return Collection of nodes not processed yet
            const NodeCollection& getPendingNodes() const { return pendingNodes; }
            /// @brief Get vector of nodes that were spawned
            /// @return Vector of nodes that were spawned
            NodeVector& getSpawnedNodes() { return spawnedNodes; }
            /// @brief Get vector of nodes that were spawned
            /// @return Vector of nodes that were spawned
            const NodeVector& getSpawnedNodes() const { return spawnedNodes; }

        private:
            /// @brief Collection of nodes that weren't processed yet
            NodeCollection& pendingNodes;
            /// @brief Vector of spawned nodes
            NodeVector& spawnedNodes;
            /// @brief Index of node being processed
            std::size_t currentIndex;
            /// @brief Size of each node
            float nodeSize;
        };

        /// @brief Check if node has an node following the given direction and spawn a new node
        /// @tparam NodeCollection Collection of pending nodes (stack or queue)
        /// @param data Generation data containing the spawned nodes and pending nodes
        /// @param currentDirection Direction from current to adjacent node
        /// @param flippedDirection Direction from adjacent to current node
        template<typename NodeCollection>
        void checkAdjacentNode(WaveFunctionCollapseData<NodeCollection>& data, utility::enums::Direction currentDirection, utility::enums::Direction flippedDirection)
        {
            if (!data.getCurrentNode().hasAdjacentNode(currentDirection))
            {
                return;
            }

            math::Vector3 adjacentPosition = getAdjacentNodePosition(data.getCurrentNode().getPosition(), currentDirection, data.getNodeSize());
            std::optional<NodeVector::iterator> adjacentNode = spawnNode(data.getPendingNodes(), data.getSpawnedNodes(), adjacentPosition);

            if (!adjacentNode.has_value())
            {
                data.getLastSpawnedNode().addAdjacentNode(flippedDirection);
            }
            else if (!adjacentNode.value()->hasAdjacentNode(flippedDirection))
            {
                data.getCurrentNode().removeAdjacentNode(currentDirection);
            }
        }

        /// @brief Spawn nodes adjacent to current node
        /// @tparam NodeCollection Collection of pending nodes (stack or queue)
        /// @param spawnedNodes Vector of nodes spawned in level
        /// @param pendingNodes Collection of nodes that weren't processed yet
        /// @param currentIndex Index of node being processed
        /// @param directions Directions that can be used to reach adjacent node
        /// @param nodeSize Size of each node
        template<typename NodeCollection>
        void spawnAdjacentNodes(NodeVector& spawnedNodes, NodeCollection& pendingNodes, std::size_t currentIndex, const std::vector<utility::enums::Direction> directions, float nodeSize)
        {
            const int adjacentNodes = spawnedNodes.at(currentIndex).getAdjacentNodesCount();

            if (adjacentNodes >= directions.size())
            {
                return;
            }

            int additionalNeighbors = math::Random::generateNumber(1, directions.size() - adjacentNodes + 1);
            spawnedNodes.at(currentIndex).generateAdjacentNodes(additionalNeighbors, directions);
            WaveFunctionCollapseData wfcData(pendingNodes, spawnedNodes, currentIndex, nodeSize);
            std::for_each(begin(directions), end(directions),
                [&wfcData](utility::enums::Direction direction)
                {
                    checkAdjacentNode(wfcData, direction, utility::enums::getFlippedDirection(direction));
                });
        }

        /// @brief Generate a level using the Wave Function Collapse Algorithm
        /// @tparam NodeCollection Collection of pending nodes (stack or queue)
        /// @param data Object containing number of nodes that need to be generated, node size & starting position
        /// @param directions Directions that can be used to reach adjacent node
        /// @param callback Callback when a node is generated
        template<typename NodeCollection>
        void waveFunctionCollapse(const GenerationData& data, std::vector<utility::enums::Direction>&& directions, utility::CallbackFunctor<void(math::Vector3, utility::enums::Direction)>&& callback)
        {
            NodeCollection pendingNodes{};
            NodeVector spawnedNodes{};
            spawnedNodes.reserve(data.count);
            spawnNode(pendingNodes, spawnedNodes, data.startPoint);
            std::default_random_engine rd{ math::Random::seed };

            while (!pendingNodes.empty())
            {
                std::ostringstream oss{};
                std::size_t currentIndex = getNext(pendingNodes);
                pendingNodes.pop();

                const math::Vector3& position = spawnedNodes.at(currentIndex).getPosition();
                oss << "Current Node: " << position.x << " " << position.y << " " << position.z;
                utility::logInfo(oss.str());

                if (spawnedNodes.size() < data.count)
                {
                    std::shuffle(begin(directions), end(directions), rd);
                    spawnAdjacentNodes(spawnedNodes, pendingNodes, currentIndex, directions, data.size);
                }

                callback(spawnedNodes.at(currentIndex).getPosition(), spawnedNodes.at(currentIndex).getAdjacentNodes());
            }

            utility::logInfo("Wave Function Collapsed Spawned: " + std::to_string(spawnedNodes.size()));
        }
    }

    void waveFunctionCollapse(const GenerationData& data, ExpansionMode mode, math::Axis axes, utility::CallbackFunctor<void(math::Vector3, utility::enums::Direction)>&& callback)
    {
        if (mode == ExpansionMode::DFS)
        {
            utility::logInfo("DFS WFC Started");
            waveFunctionCollapse<std::stack<std::size_t>>(data, getDirections(axes), std::move(callback));
            utility::logInfo("DFS WFC Ended");
        }
        else if (mode == ExpansionMode::BFS)
        {
            utility::logInfo("BFS WFC Started");
            waveFunctionCollapse<std::queue<std::size_t>>(data, getDirections(axes), std::move(callback));
            utility::logInfo("BFS WFC Ended");
        }
    }
}
