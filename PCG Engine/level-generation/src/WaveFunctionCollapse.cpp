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
        using DirectionPair = std::tuple<utility::enums::Direction, utility::enums::Direction>;

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

        math::Vector3 getNeighborPosition(const math::Vector3& currentPosition, utility::enums::Direction side, float size)
        {
            switch (side)
            {
            case utility::enums::Direction::left:
            {
                return currentPosition + math::Vector3::left * size;
            }
            case utility::enums::Direction::right:
            {
                return currentPosition + math::Vector3::right * size;
            }
            case utility::enums::Direction::forward:
            {
                return currentPosition + math::Vector3::forward * size;
            }
            case utility::enums::Direction::backward:
            {
                return currentPosition + math::Vector3::backward * size;
            }
            case utility::enums::Direction::up:
            {
                return currentPosition + math::Vector3::up * size;
            }
            case utility::enums::Direction::down:
            {
                return currentPosition + math::Vector3::down * size;
            }
            default:
            {
                return currentPosition;
            }
            }
        }

        void addNeighborToSpawnedNode(Node& spawnedNode, utility::enums::Direction side)
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
        void checkNeighbor(WaveFunctionCollapseData<NodeCollection>& data, utility::enums::Direction currentSide, utility::enums::Direction flippedSide)
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
        void checkNeighborPair(WaveFunctionCollapseData<NodeCollection>& data, utility::enums::Direction side, utility::enums::Direction flippedSide)
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

        std::vector<utility::enums::Direction> getShuffledDirections(const std::vector<DirectionPair>& directionPairs, std::default_random_engine& rd)
        {
            std::vector<utility::enums::Direction> directions{};

            for (const auto& direction : directionPairs)
            {
                directions.emplace_back(std::get<0>(direction));
                directions.emplace_back(std::get<1>(direction));
            }

            std::shuffle(begin(directions), end(directions), rd);

            return directions;
        }

        template<typename NodeCollection>
        void waveFunctionCollapse(GenerationData* data, std::vector<DirectionPair>&& directionPairs, utility::CallbackFunctor<void(math::Vector3, utility::enums::Direction)>&& callback)
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

                std::shuffle(begin(directionPairs), end(directionPairs), rd);

                if (spawnedNodes.size() < data->limit)
                {
                    const int neighborCount = spawnedNodes.at(currentIndex).getNeighbors().getNeighborCount();

                    if (neighborCount < directionPairs.size() * 2)
                    {
                        int additionalNeighbors = math::Random::generate(1, directionPairs.size() * 2 - neighborCount + 1);
                        spawnedNodes.at(currentIndex).getNeighbors().generateNeighbors(additionalNeighbors, getShuffledDirections(directionPairs, rd));
                    }
                }

                WaveFunctionCollapseData wfcData(pushedNodes, spawnedNodes, currentIndex, data->size);

                for (const auto& directionPair : directionPairs)
                {
                    checkNeighborPair(wfcData, std::get<0>(directionPair), std::get<1>(directionPair));
                }

                callback(spawnedNodes.at(currentIndex).getPosition(), spawnedNodes.at(currentIndex).getNeighbors().getNeighbors());
            }

            utility::logInfo("Wave Function Collapsed Spawned: " + std::to_string(spawnedNodes.size()));
        }
    }

    void waveFunctionCollapse(GenerationData* data, ExpansionMode mode, math::axis::Flag axis, utility::CallbackFunctor<void(math::Vector3, utility::enums::Direction)>&& callback)
    {
        std::vector<DirectionPair> directionPairs{};

        if ((axis & math::axis::x) > 0)
        {
            directionPairs.emplace_back(DirectionPair{ utility::enums::Direction::left, utility::enums::Direction::right });
        }

        if ((axis & math::axis::y) > 0)
        {
            directionPairs.emplace_back(DirectionPair{ utility::enums::Direction::up, utility::enums::Direction::down });
        }

        if ((axis & math::axis::z) > 0)
        {
            directionPairs.emplace_back(DirectionPair{ utility::enums::Direction::forward, utility::enums::Direction::backward });
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
