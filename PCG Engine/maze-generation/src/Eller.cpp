#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/Eller.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <algorithm>
#include <random>
#include <unordered_map>

namespace pcg::engine::maze_generation
{
    namespace
    {
        using NodesSet = std::unordered_map<NodeCoordinates, int>;
        using Sets = std::unordered_map<int, std::vector<NodeCoordinates>>;
        using ConnectedSet = std::vector<int>;

        /// @brief Contains nodes map and sets map used to keep track of connected nodes
        struct EllerGenerationInfo
        {
            /// @brief Add node coordinate to map of sets and nodes
            /// @param current Current node coordinates
            void initializeNode(const NodeCoordinates& current)
            {
                if (nodes.find(current) == end(nodes))
                {
                    nodes.insert({ current,  currentSet });
                    sets.insert({ currentSet++, { current } });
                }
            }
            /// @brief Add current and adjacent node to map of sets and nodes
            /// @param current Current node coordinates
            /// @param adjacent Adjacent node coordinates
            void initializeNodePair(const NodeCoordinates& current, const NodeCoordinates& adjacent)
            {
                initializeNode(current);
                initializeNode(adjacent);
            }
            /// @brief Returns true if node coordinate belongs to same set
            /// @param currentNode Current node coordinates
            /// @param adjacentNode Adjacent node coordinates
            /// @return True if nodes belong to same set
            bool areConnected(const NodeCoordinates& currentNode, const NodeCoordinates& adjacentNode) const
            {
                auto currentNodeSet = nodes.find(currentNode);
                auto adjacentNodeSet = nodes.find(adjacentNode);
                const bool nodesExists = currentNodeSet != end(nodes) && adjacentNodeSet != end(nodes);
                return nodesExists && currentNodeSet->second == adjacentNodeSet->second;
            }
            /// @brief Merge two sets together
            /// @param sinkNode Node who's set will remain
            /// @param targetNode Node that will be merged with the set of sink node
            void merge(const NodeCoordinates& sinkNode, const NodeCoordinates& targetNode)
            {
                const int sinkSet = nodes[sinkNode];
                const int targetSet = nodes[targetNode];

                sets[sinkSet].append_range(sets[targetSet]);
                std::for_each(begin(sets[targetSet]), end(sets[targetSet]), [this, sinkSet](const NodeCoordinates& coordinate) { nodes[coordinate] = sinkSet; });
                sets.erase(targetSet);
            }
            /// @brief Add node to nodes and sets maps
            /// @param node Node being added
            /// @param set Set id
            void add(NodeCoordinates&& node, int set)
            {
                nodes.insert({ node, set });
                sets[set].emplace_back(node);
            }

            /// @brief Map of each nodes set
            NodesSet nodes{};
            /// @brief Map of vector of nodes of each set
            Sets sets{};
            /// @brief Random engine used to shuffle vectors
            std::default_random_engine randomEngine = math::Random::getDefaultEngine();
            /// @brief Current active set
            int currentSet = 0;
        };

        /// @brief RowInfo contains info about the row being processed
        struct RowInfo
        {
            RowInfo(int y, bool last) : connectedSet(1, 0), yCoordinate(y), lastRow(last)
            {
            }

            /// @brief End current set and add x to new set
            /// @param x New set starting position
            void endCurrentSet(int x)
            {
                connectedSets.emplace_back(std::move(connectedSet));
                connectedSet = ConnectedSet(1, x);
            }

            /// @brief Add the last set in the row to the connectedSets
            void addLastSet()
            {
                connectedSets.emplace_back(std::move(connectedSet));
            }

            /// @brief Vector of joint cell in row
            std::vector<ConnectedSet> connectedSets{};
            /// @brief Current set of joint cell
            ConnectedSet connectedSet;
            /// @brief Row y coordinate
            int yCoordinate;
            /// @brief Last row in maze
            bool lastRow;
        };

        /// @brief Join cells in the current row into multiple sets
        /// @param info MazeGeneration info
        /// @param row Current row sets info
        /// @param currentNode Current node coordinates
        /// @param grid Grid representing maze
        /// @param callback User defined callback nullptr if callback should be invoked after maze generation
        void joinCells(EllerGenerationInfo& info, RowInfo& row, NodeCoordinates&& currentNode, Grid& grid, MazeCallback* callback)
        {
            NodeCoordinates adjacentNode{ currentNode.x + 1, currentNode.y };
            info.initializeNodePair(currentNode, adjacentNode);
            const bool nodesConnected = info.areConnected(currentNode, adjacentNode);
            const bool newSet = !row.lastRow && math::Random::number(0, 2) == 0;

            if (nodesConnected || newSet)
            {
                utility::logInfo("Ending current run");
                row.endCurrentSet(adjacentNode.x);
            }
            else
            {
                utility::logInfo("Merging node to run");
                info.merge(currentNode, adjacentNode);
                row.connectedSet.push_back(adjacentNode.x);
                addAdjacentNodePath(currentNode, adjacentNode, NodeValue::right, grid);

                if (callback)
                {
                    invokeNodePairCallback(currentNode, adjacentNode, grid, *callback);
                }
            }
        }

        /// @brief Connect each set in the row to the next row
        /// @param info MazeGeneration info
        /// @param row Current row sets info
        /// @param grid Grid representing maze
        /// @param callback User defined callback nullptr if callback should be invoked after maze generation
        void addVerticalConnections(EllerGenerationInfo& info, RowInfo& row, Grid& grid, MazeCallback* callback)
        {
            utility::logInfo("Adding vertical connections");
            for (auto& connectedSet : row.connectedSets)
            {
                std::shuffle(begin(connectedSet), end(connectedSet), info.randomEngine);
                const int verticalConnections = math::Random::number(1, connectedSet.size());

                for (int connection = 0; connection < verticalConnections; ++connection)
                {
                    const int x = connectedSet[connection];
                    const int adjacentY = row.yCoordinate + 1;
                    addAdjacentNodePath(x, row.yCoordinate, x, adjacentY, NodeValue::forward, grid);
                    info.add({ x, adjacentY }, info.nodes[{x, row.yCoordinate}]);

                    if (callback)
                    {
                        invokeNodePairCallback(x, row.yCoordinate, x, adjacentY, grid, *callback);
                    }
                }
            }
        }
    }

    void eller(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        utility::logInfo("Eller Maze Generation Started");

        Grid grid = generateGrid(width, height);
        EllerGenerationInfo info{};
        MazeCallback* callbackPtr = invokeAfterGeneration ? nullptr : &callback;

        for (int y = 0; y < height; ++y)
        {
            RowInfo rowInfo(y, y == height - 1);

            for (int x = 0; x < width - 1; ++x)
            {
                joinCells(info, rowInfo, { x, y }, grid, callbackPtr);
            }

            rowInfo.addLastSet();

            if (!rowInfo.lastRow)
            {
                addVerticalConnections(info, rowInfo, grid, callbackPtr);
            }
        }

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }

        utility::logInfo("Eller Maze Generation Ended");
    }
}
