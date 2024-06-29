#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/Kruskal.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <random>
#include <vector>

namespace pcg::engine::maze_generation
{
    namespace
    {
        class Tree
        {
        public:
            Tree* getRoot()
            {
                return parent ? parent->getRoot() : this;
            }

            const Tree* getRoot() const
            {
                return parent ? parent->getRoot() : this;
            }

            bool isConnected(const Tree& tree) const
            {
                return getRoot() == tree.getRoot();
            }

            void addSubTree(Tree& tree)
            {
                tree.getRoot()->parent = this;
            }

        private:
            Tree* parent = nullptr;
        };

        struct Edge
        {
            int x;
            int y;
            NodeValue direction;
        };

        using EdgesVector = std::vector<Edge>;
        using TreeGrid = std::vector<std::vector<Tree>>;

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

            std::default_random_engine randomEngine{ math::Random::seed };
            std::shuffle(begin(edges), end(edges), randomEngine);
            return edges;
        }
    }

    void kruskal(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
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
    }
}
