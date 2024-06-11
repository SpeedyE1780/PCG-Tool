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
