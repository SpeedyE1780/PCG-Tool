#include <pcg/engine/core/api.hpp>
#include <pcg/engine/core/generators.hpp>
#include <pcg/engine/core/GenerationData.hpp>
#include <pcg/engine/core/node.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <functional>
#include <optional>
#include <queue>
#include <stack>
#include <sstream>
#include <unordered_set>

namespace pcg::engine::core
{
    static std::optional<math::Vector3> getNextPosition(std::unordered_set<math::Vector3, math::Vector3Hash>& positions, const math::Vector3& currentPosition, const std::vector<const math::Vector3*>& directions, float offset)
    {
        std::vector<math::Vector3> availablePositions{};

        for (const auto* direction : directions)
        {
            math::Vector3 position = currentPosition + *direction * offset;

            if (positions.find(position) == end(positions))
            {
                availablePositions.emplace_back(std::move(position));
            }
        }

        if (availablePositions.size() == 0)
        {
            return std::nullopt;
        }

        return availablePositions[math::Random::generate(0, availablePositions.size())];
    }

    static void multiDimensionalGeneration(GenerationData* data, const std::vector<const math::Vector3*>& directions, bool disableOverlap, addPointCallback callback)
    {
        utility::logInfo("Multi-Dimension Generation Started");

        std::unordered_set<math::Vector3, math::Vector3Hash> positions{};
        math::Vector3 position = data->startPoint;

        for (int i = 0; i < data->limit; i++)
        {
            callback(position);

            if (disableOverlap)
            {
                positions.insert(position);
            }

            auto nextPosition = getNextPosition(positions, position, directions, data->size);

            if (!nextPosition.has_value())
            {
                utility::logInfo("Multi-Dimension Generation Ended Early");
                return;
            }

            position = nextPosition.value();
        }

        utility::logInfo("Multi-Dimension Generation Ended");
    }

    void generation2D(GenerationData* data, math::Plane plane, bool disableOverlap, addPointCallback callback)
    {
        std::vector<const math::Vector3*> directions{};

        switch (plane)
        {
        case math::Plane::xy:
            directions.insert(begin(directions), { &math::Vector3::right, &math::Vector3::left, &math::Vector3::up, &math::Vector3::down });
            break;
        case math::Plane::xz:
            directions.insert(begin(directions), { &math::Vector3::right, &math::Vector3::left, &math::Vector3::forward, &math::Vector3::backward });
            break;
        case math::Plane::yz:
            directions.insert(begin(directions), { &math::Vector3::up, &math::Vector3::down, &math::Vector3::forward, &math::Vector3::backward });
            break;
        default:
            break;
        }

        multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback)
    {
        static const std::vector<const math::Vector3*> directions{ {&math::Vector3::right, &math::Vector3::left, &math::Vector3::up, &math::Vector3::down, &math::Vector3::forward, &math::Vector3::backward} };
        multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    template<typename collection>
    static bool pushNode(collection& nodeCollection, std::vector<Node>& vector, const math::Vector3& position)
    {
        std::ostringstream oss{};

        oss << "Node: " << position.x << " " << position.y << " " << position.z << " ";
        auto nodeIterator = std::find_if(begin(vector), end(vector), [&position](const Node& node)
            {
                return node.getPosition() == position;
            });

        if (nodeIterator == vector.end())
        {
            nodeCollection.push(vector.size());
            vector.emplace_back(Node(position));
            oss << "added";
            utility::logInfo(oss.str());
            return true;
        }

        oss << "already addded";
        utility::logWarning(oss.str());
        return false;
    }

    static void waveFunctionCollapseDFS(GenerationData* data, addWFCPointCallback callback)
    {
        utility::logInfo("WFC Started");
        std::stack<std::size_t> pushedNodes{};
        std::vector<Node> spawnedNodes{};
        spawnedNodes.reserve(data->limit);
        pushNode(pushedNodes, spawnedNodes, data->startPoint);

        while (!pushedNodes.empty())
        {
            std::ostringstream oss{};
            std::size_t currentIndex = pushedNodes.top();
            pushedNodes.pop();
            const math::Vector3& position = spawnedNodes.at(currentIndex).getPosition();
            oss << "Current: " << position.x << " " << position.y << " " << position.z;
            utility::logInfo(oss.str());

            if (spawnedNodes.size() < data->limit)
            {
                spawnedNodes.at(currentIndex).getNeighbors().generateNeighbors();
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::left))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::left * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::right);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::right))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::left);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::right))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::right * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::left);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::left))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::right);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::forward))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::forward * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::backward);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::backward))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::forward);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::backward))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::backward * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::forward);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::forward))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::backward);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::up))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::up * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::down);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::down))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::up);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::down))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::down * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::up);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::up))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::down);
                    }
                }
            }

            callback(spawnedNodes.at(currentIndex).getPosition(), spawnedNodes.at(currentIndex).getNeighbors().getIntegerRepresentation());
        }

        utility::logInfo("Wave Function Collapsed Spawned: " + std::to_string(spawnedNodes.size()));
        utility::logInfo("WFC Ended");
    }

    static void waveFunctionCollapseBFS(GenerationData* data, addWFCPointCallback callback)
    {
        utility::logInfo("WFC Started");
        std::queue<std::size_t> pushedNodes{};
        std::vector<Node> spawnedNodes{};
        spawnedNodes.reserve(data->limit);
        pushNode(pushedNodes, spawnedNodes, data->startPoint);

        while (!pushedNodes.empty())
        {
            std::ostringstream oss{};
            std::size_t currentIndex = pushedNodes.front();
            pushedNodes.pop();
            const math::Vector3& position = spawnedNodes.at(currentIndex).getPosition();
            oss << "Current: " << position.x << " " << position.y << " " << position.z;
            utility::logInfo(oss.str());

            if (spawnedNodes.size() < data->limit)
            {
                spawnedNodes.at(currentIndex).getNeighbors().generateNeighbors();
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::left))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::left * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::right);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::right))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::left);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::right))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::right * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::left);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::left))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::right);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::forward))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::forward * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::backward);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::backward))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::forward);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::backward))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::backward * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::forward);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::forward))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::backward);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::up))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::up * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::down);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::down))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::up);
                    }
                }
            }

            if (spawnedNodes.at(currentIndex).getNeighbors().hasNeighbor(Neighbors::down))
            {
                math::Vector3 neighborPosition = spawnedNodes.at(currentIndex).getPosition() + math::Vector3::down * data->size;

                if (pushNode(pushedNodes, spawnedNodes, neighborPosition))
                {
                    spawnedNodes.back().getNeighbors().addNeighbor(Neighbors::up);
                }
                else
                {
                    auto nodeIterator = std::find_if(begin(spawnedNodes), end(spawnedNodes), [&neighborPosition](const Node& node)
                        {
                            return node.getPosition() == neighborPosition;
                        });

                    if (!nodeIterator->getNeighbors().hasNeighbor(Neighbors::up))
                    {
                        spawnedNodes.at(currentIndex).getNeighbors().removeNeighbor(Neighbors::down);
                    }
                }
            }

            callback(spawnedNodes.at(currentIndex).getPosition(), spawnedNodes.at(currentIndex).getNeighbors().getIntegerRepresentation());
        }

        utility::logInfo("Wave Function Collapsed Spawned: " + std::to_string(spawnedNodes.size()));
        utility::logInfo("WFC Ended");
    }

    void waveFunctionCollapse(GenerationData* data, ExpansionMode mode, addWFCPointCallback callback)
    {
        if (mode == ExpansionMode::DFS)
        {
            waveFunctionCollapseDFS(data, callback);
        }
        else if (mode == ExpansionMode::BFS)
        {
            waveFunctionCollapseBFS(data, callback);
        }
    }
}
