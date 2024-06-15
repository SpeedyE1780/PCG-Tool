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

        template<typename NodeCollection>
        std::optional<NodeVector::iterator> pushNode(NodeCollection& pendingNodes, NodeVector& spawnedNodes, const math::Vector3& position)
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

        template<typename T>
        T getNext(const std::queue<T>& collection)
        {
            return collection.front();
        }

        template<typename T>
        T getNext(const std::stack<T>& collection)
        {
            return collection.top();
        }

        math::Vector3 getNeighborPosition(const math::Vector3& currentPosition, int side, float size)
        {
            switch (side)
            {
            case Neighbors::left:
            {
                return currentPosition + math::Vector3::left * size;
            }
            case Neighbors::right:
            {
                return currentPosition + math::Vector3::right * size;
            }
            case Neighbors::forward:
            {
                return currentPosition + math::Vector3::forward * size;
            }
            case Neighbors::backward:
            {
                return currentPosition + math::Vector3::backward * size;
            }
            case Neighbors::up:
            {
                return currentPosition + math::Vector3::up * size;
            }
            case Neighbors::down:
            {
                return currentPosition + math::Vector3::down * size;
            }
            default:
            {
                return currentPosition;
            }
            }
        }

        void addNeighborToSpawnedNode(Node& spawnedNode, int side)
        {
            spawnedNode.getNeighbors().addNeighbor(side);
        }

        template<typename NodeCollection>
        class WaveFunctionCollapseData
        {
        public:
            WaveFunctionCollapseData(NodeCollection& pushedNodes, NodeVector& spawnedNodes, std::size_t currentIndex, float size) :
                pushedNodes(pushedNodes),
                spawnedNodes(spawnedNodes),
                currentIndex(currentIndex),
                nodeSize(size)
            {
            }

            Node& getCurrentNode() { return spawnedNodes.at(currentIndex); }
            const Node& getCurrentNode() const { return spawnedNodes.at(currentIndex); }
            Node& getLastSpawnedNode() { return spawnedNodes.back(); }
            const Node& getLastSpawnedNode() const { return spawnedNodes.back(); }
            float getNodeSize() const { return nodeSize; }
            NodeCollection& getPushedNodes() { return pushedNodes; }
            const NodeCollection& getPushedNodes() const { return pushedNodes; }
            NodeVector& getSpawnedNodes() { return spawnedNodes; }
            const NodeVector& getSpawnedNodes() const { return spawnedNodes; }

        private:
            NodeCollection& pushedNodes;
            NodeVector& spawnedNodes;
            std::size_t currentIndex;
            float nodeSize;
        };

        template<typename NodeCollection>
        void checkNeighbor(WaveFunctionCollapseData<NodeCollection>& data, int currentSide, int flippedSide)
        {
            if (!data.getCurrentNode().getNeighbors().hasNeighbor(currentSide))
            {
                return;
            }

            math::Vector3 neighborPosition = getNeighborPosition(data.getCurrentNode().getPosition(), currentSide, data.getNodeSize());
            std::optional<NodeVector::iterator> neighborNode = pushNode(data.getPushedNodes(), data.getSpawnedNodes(), neighborPosition);

            if (!neighborNode.has_value())
            {
                addNeighborToSpawnedNode(data.getLastSpawnedNode(), flippedSide);
            }
            else if (!neighborNode.value()->getNeighbors().hasNeighbor(flippedSide))
            {
                data.getCurrentNode().getNeighbors().removeNeighbor(currentSide);
            }
        }

        template<typename NodeCollection>
        void checkNeighborPair(WaveFunctionCollapseData<NodeCollection>& data, int side, int flippedSide)
        {
            if (math::Random::generate(0, 2) == 0)
            {
                checkNeighbor(data, side, flippedSide);
                checkNeighbor(data, flippedSide, side);
            }
            else
            {
                checkNeighbor(data, flippedSide, side);
                checkNeighbor(data, side, flippedSide);
            }
        }

        template<typename NodeCollection>
        void waveFunctionCollapse(GenerationData* data, std::vector<std::tuple<int, int>>&& directionPairs, utility::CallbackFunctor<void(math::Vector3, int)>&& callback)
        {
            NodeCollection pushedNodes{};
            NodeVector spawnedNodes{};
            spawnedNodes.reserve(data->limit);
            pushNode(pushedNodes, spawnedNodes, data->startPoint);
            std::default_random_engine rd{};

            while (!pushedNodes.empty())
            {
                std::ostringstream oss{};
                std::size_t currentIndex = getNext(pushedNodes);
                pushedNodes.pop();

                const math::Vector3& position = spawnedNodes.at(currentIndex).getPosition();
                oss << "Current Node: " << position.x << " " << position.y << " " << position.z;
                utility::logInfo(oss.str());

                if (spawnedNodes.size() < data->limit)
                {
                    spawnedNodes.at(currentIndex).getNeighbors().generateNeighbors();
                }

                WaveFunctionCollapseData wfcData(pushedNodes, spawnedNodes, currentIndex, data->size);
                std::shuffle(begin(directionPairs), end(directionPairs), rd);

                for (const auto& directionPair : directionPairs)
                {
                    checkNeighborPair(wfcData, std::get<0>(directionPair), std::get<1>(directionPair));
                }

                callback(spawnedNodes.at(currentIndex).getPosition(), spawnedNodes.at(currentIndex).getNeighbors().getIntegerRepresentation());
            }

            utility::logInfo("Wave Function Collapsed Spawned: " + std::to_string(spawnedNodes.size()));
        }
    }

    void waveFunctionCollapse(GenerationData* data, ExpansionMode mode, math::axis::Flag axis, utility::CallbackFunctor<void(math::Vector3, int)>&& callback)
    {
        std::vector<std::tuple<int, int>> directionPairs{};

        if ((axis & math::axis::x) > 0)
        {
            directionPairs.emplace_back(std::tuple<int, int>{ Neighbors::left, Neighbors::right });
        }

        if ((axis & math::axis::y) > 0)
        {
            directionPairs.emplace_back(std::tuple<int, int>{ Neighbors::up, Neighbors::down });
        }

        if ((axis & math::axis::z) > 0)
        {
            directionPairs.emplace_back(std::tuple<int, int>{ Neighbors::forward, Neighbors::backward });
        }

        if (mode == ExpansionMode::DFS)
        {
            utility::logInfo("DFS WFC Started");
            waveFunctionCollapse<std::stack<std::size_t>>(data, std::move(directionPairs), std::move(callback));
            utility::logInfo("DFS WFC Ended");
        }
        else if (mode == ExpansionMode::BFS)
        {
            utility::logInfo("BFS WFC Started");
            waveFunctionCollapse<std::queue<std::size_t>>(data, std::move(directionPairs), std::move(callback));
            utility::logInfo("BFS WFC Ended");
        }
    }
}
