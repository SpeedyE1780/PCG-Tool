#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/GrowingTree.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <functional>
#include <random>
#include <tuple>

namespace pcg::engine::maze_generation
{
    namespace
    {
        /// @brief Get oldest node
        /// @param pendingNodes Pending nodes that still has adjacent nodes
        /// @return Oldest node
        NodeCoordinates getOldestNode(const std::vector<NodeCoordinates>& pendingNodes)
        {
            return pendingNodes[0];
        }

        /// @brief Get node in the middle of vector
        /// @param pendingNodes Pending nodes that still has adjacent nodes
        /// @return Node in the middle of vector
        NodeCoordinates getMiddleNode(const std::vector<NodeCoordinates>& pendingNodes)
        {
            return pendingNodes[pendingNodes.size() / 2];
        }

        /// @brief Get newest node
        /// @param pendingNodes Pending nodes that still has adjacent nodes
        /// @return Newest node
        NodeCoordinates getNewestNode(const std::vector<NodeCoordinates>& pendingNodes)
        {
            return pendingNodes[pendingNodes.size() - 1];
        }

        /// @brief Get random node
        /// @param pendingNodes Pending nodes that still has adjacent nodes
        /// @return Random node
        NodeCoordinates getRandomNode(const std::vector<NodeCoordinates>& pendingNodes)
        {
            return pendingNodes[math::Random::generateNumber(0, pendingNodes.size())];
        }

        /// @brief Generate maze with growing tree
        /// @param width Grid width
        /// @param height Grid height
        /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
        /// @param getNextNode Function to get the next node to process
        /// @param callback Callback when a node is generated
        void generateGrowingTree(int width, int height, bool invokeAfterGeneration, std::function<NodeCoordinates(const std::vector<NodeCoordinates>& nodes)> getNextNode, MazeCallback&& callback)
        {
            Grid grid = generateGrid(width, height);
            Directions directions = getDefaultDirections();
            std::default_random_engine randomEngine{ math::Random::seed };

            std::vector<NodeCoordinates> nodes(1, getRandomStartingNode(width, height));

            while (!nodes.empty())
            {
                auto [x, y] = getNextNode(nodes);

                std::shuffle(begin(nodes), end(nodes), randomEngine);
                bool noAdjacentNode = true;

                for (NodeValue direction : directions)
                {
                    if (auto [adjacentX, adjacentY] = getAdjacentCoordinates(x, y, direction); isWithinGridBounds(adjacentX, adjacentY, width, height) && grid[adjacentY][adjacentX] == NodeValue::none)
                    {
                        addAdjacentNodePath(x, y, adjacentX, adjacentY, direction, grid);

                        if (!invokeAfterGeneration)
                        {
                            invokeNodePairCallback(x, y, adjacentX, adjacentY, grid, callback);
                        }

                        noAdjacentNode = false;
                        nodes.emplace_back(NodeCoordinates{ adjacentX, adjacentY });
                    }
                }

                if (noAdjacentNode)
                {
                    std::erase(nodes, NodeCoordinates{ x, y });
                }
            }

            if (invokeAfterGeneration)
            {
                invokeCallback(grid, callback);
            }
        }
    }

    void growingTree(int width, int height, bool invokeAfterGeneration, GrowingTreeSelectionMethod method, MazeCallback&& callback)
    {
        switch (method)
        {
        case GrowingTreeSelectionMethod::oldest:
        {
            generateGrowingTree(width, height, invokeAfterGeneration, getOldestNode, std::move(callback));
            break;
        }
        case GrowingTreeSelectionMethod::middle:
        {
            generateGrowingTree(width, height, invokeAfterGeneration, getMiddleNode, std::move(callback));
            break;
        }
        case GrowingTreeSelectionMethod::newest:
        {
            generateGrowingTree(width, height, invokeAfterGeneration, getNewestNode, std::move(callback));
            break;
        }
        case GrowingTreeSelectionMethod::random:
        {
            generateGrowingTree(width, height, invokeAfterGeneration, getRandomNode, std::move(callback));
            break;
        }
        default:
        {
            break;
        }
        }
    }

    void growingTree(int width, int height, bool invokeAfterGeneration, utility::CallbackFunctor<int(int)>&& nodeSelectionCallback, MazeCallback&& callback)
    {
        generateGrowingTree(width, height, invokeAfterGeneration, [&nodeSelectionCallback](const std::vector<NodeCoordinates>& nodes)
            {
                return nodes[nodeSelectionCallback(nodes.size())];
            }, std::move(callback));
    }
}
