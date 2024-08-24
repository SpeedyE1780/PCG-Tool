#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/Kruskal.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <random>
#include <vector>

namespace pcg::engine::maze_generation
{
    namespace
    {
        /// @brief Tree representing connected nodes
        class Tree
        {
        public:
            /// @brief Get root of tree
            /// @return Root of tree or this
            Tree* getRoot() { return parent ? parent->getRoot() : this; }
            /// @brief Get root of tree
            /// @return Root of tree or this
            const Tree* getRoot() const { return parent ? parent->getRoot() : this; }
            /// @brief Check if tree share same root
            /// @param tree other tree
            /// @return True if trees share the same root
            bool isConnected(const Tree& tree) const { return getRoot() == tree.getRoot(); }
            /// @brief Add tree as a subtree to this
            /// @param tree Subtree being added under this
            void addSubTree(Tree& tree) { tree.getRoot()->parent = this; }

        private:
            /// @brief Parent of this tree
            Tree* parent = nullptr;
        };

        /// @brief Edge between two adjacent nodes
        struct Edge
        {
            int x;
            int y;
            NodeValue direction;
        };

        using EdgesVector = std::vector<Edge>;
        using TreeGrid = std::vector<std::vector<Tree>>;

        /// @brief Get all possible edges in grid
        /// @param width Grid width
        /// @param height Grid height
        /// @return A shuffled vector of all edges in grid
        EdgesVector getEdges(int width, int height)
        {
            EdgesVector edges{};

            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    if (x < width - 1)
                    {
                        edges.emplace_back(Edge{ x, y, NodeValue::right });
                    }

                    if (y < height - 1)
                    {
                        edges.emplace_back(Edge{ x, y, NodeValue::forward });
                    }
                }
            }

            std::default_random_engine randomEngine = math::Random::getDefaultEngine();
            std::shuffle(begin(edges), end(edges), randomEngine);
            return edges;
        }
    }

    void kruskal(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
    {
        utility::logInfo("Kruskal Maze Generation Started");
        Grid grid = generateGrid(width, height);
        TreeGrid trees = TreeGrid(height, std::vector<Tree>(width));
        EdgesVector edges = getEdges(width, height);

        for (const Edge& edge : edges)
        {
            const auto& [originX, originY, direction] = edge;
            auto [endX, endY] = getAdjacentCoordinates(originX, originY, direction);

            Tree& originTree = trees[originY][originX];
            Tree& endTree = trees[endY][endX];

            if (originTree.isConnected(endTree))
            {
                continue;
            }

            originTree.addSubTree(endTree);
            addAdjacentNodePath(originX, originY, endX, endY, direction, grid);

            if (!invokeAfterGeneration)
            {
                invokeNodePairCallback(originX, originY, endX, endY, grid, callback);
            }
        }

        if (invokeAfterGeneration)
        {
            invokeCallback(grid, callback);
        }

        utility::logInfo("Kruskal Maze Generation Ended");
    }
}
