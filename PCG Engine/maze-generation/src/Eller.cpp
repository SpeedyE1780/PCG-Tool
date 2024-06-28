#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/Eller.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <algorithm>
#include <random>
#include <unordered_map>

namespace pcg::engine::maze_generation
{
    using NodesSet = std::unordered_map<NodeCoordinates, int>;
    using Sets = std::unordered_map<int, std::vector<NodeCoordinates>>;

    namespace
    {
        void initializeNodes(NodesSet& nodes, Sets& sets, int& currentSet, NodeCoordinates&& current)
        {
            if (auto iterator = nodes.find(current); iterator == end(nodes))
            {
                nodes.insert({ current,  currentSet });
                sets.insert({ currentSet++, { current } });
            }
        }

        bool areConnected(const NodesSet& nodes, NodeCoordinates&& lhs, NodeCoordinates&& rhs)
        {
            auto lhsSet = nodes.find(lhs);
            auto rhsSet = nodes.find(rhs);
            const bool nodesExists = lhsSet != end(nodes) && rhsSet != end(nodes);
            return nodesExists && lhsSet->second == rhsSet->second;
        }

        void merge(NodesSet& nodes, Sets& sets, NodeCoordinates&& sinkNode, NodeCoordinates&& targetNode)
        {
            const int sinkSet = nodes[sinkNode];
            const int targetSet = nodes[targetNode];

            sets[sinkSet].append_range(sets[targetSet]);
            std::for_each(begin(sets[targetSet]), end(sets[targetSet]), [&nodes, sinkSet](const NodeCoordinates& coordinate) { nodes[coordinate] = sinkSet; });
            sets.erase(targetSet);
        }

        void add(NodesSet& nodes, Sets& sets, NodeCoordinates&& node, int set)
        {
            nodes.insert({ node, set });
            sets[set].emplace_back(node);
        }
    }

    void eller(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        Grid grid = generateGrid(width, height);
        NodesSet nodes;
        Sets sets;
        int currentSet = 0;
        std::default_random_engine randomEngine{ math::Random::seed };

        for (int y = 0; y < height; ++y)
        {
            std::vector<std::vector<int>> connectedSets{};
            std::vector<int> connectedSet(1, 0);
            const bool lastRow = y == height - 1;

            for (int x = 0; x < width - 1; ++x)
            {
                initializeNodes(nodes, sets, currentSet, { x, y });
                initializeNodes(nodes, sets, currentSet, { x + 1, y });
                bool nodesConnected = areConnected(nodes, { x, y }, { x + 1, y });
                bool newSet = !lastRow && math::Random::generateNumber(0, 1) == 0;
                if (nodesConnected || newSet)
                {
                    connectedSets.emplace_back(std::move(connectedSet));
                    connectedSet = std::vector<int>{};
                    connectedSet.push_back(x + 1);
                }
                else
                {
                    merge(nodes, sets, { x, y }, { x + 1, y });
                    connectedSet.push_back(x + 1);
                    const int adjacentX = x + 1;
                    grid[y][x] |= NodeValue::right;
                    grid[y][adjacentX] |= NodeValue::left;

                    if (!invokeAfterGeneration)
                    {
                        callback(x, y, grid[y][x]);
                        callback(adjacentX, y, grid[y][adjacentX]);
                    }
                }
            }

            connectedSets.emplace_back(std::move(connectedSet));

            if (!lastRow)
            {
                for (auto& connectedSet : connectedSets)
                {
                    std::shuffle(begin(connectedSet), end(connectedSet), randomEngine);
                    int verticalConnections = math::Random::generateNumber(1, connectedSet.size());

                    for (int connection = 0; connection < verticalConnections; ++connection)
                    {
                        const int x = connectedSet[connection];
                        const int adjacentY = y + 1;
                        grid[y][x] |= NodeValue::forward;
                        grid[adjacentY][x] |= NodeValue::backward;
                        add(nodes, sets, { x, adjacentY }, nodes[{x, y}]);

                        if (!invokeAfterGeneration)
                        {
                            callback(x, y, grid[y][x]);
                            callback(x, adjacentY, grid[adjacentY][x]);
                        }
                    }
                }
            }
        }

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }
    }
}
