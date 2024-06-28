#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/BlobbyDivision.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <memory>
#include <optional>
#include <random>
#include <stack>
#include <tuple>
#include <unordered_map>

namespace pcg::engine::maze_generation
{
    namespace
    {
        struct Node;
        class Region;
        using NodePointer = std::shared_ptr<Node>;
        using NodeMap = std::unordered_map<NodeCoordinates, NodePointer>;
        /// @brief A threshold lower than 4 will create subregion that are cut off from the rest of the maze
        constexpr int minimumThreshold = 4;
        constexpr int smallThreshold = 10;
        constexpr int mediumThreshold = 25;
        constexpr int largeThreshold = 40;
        constexpr int hugeThreshold = 70;

        struct WallInfo
        {
            int x;
            int y;
            NodeValue direction;
        };

        struct Node
        {
            Node(int x, int y, int width, int height) : coordinates({ x, y })
            {
                if (x > 0)
                {
                    left = getAdjacentCoordinates(coordinates, NodeValue::left);
                }

                if (x < width - 1)
                {
                    right = getAdjacentCoordinates(coordinates, NodeValue::right);
                }

                if (y > 0)
                {
                    backward = getAdjacentCoordinates(coordinates, NodeValue::backward);
                }

                if (y < height - 1)
                {
                    forward = getAdjacentCoordinates(coordinates, NodeValue::forward);
                }
            }

            std::vector<NodeCoordinates> getAdjacentNodeCoordinates() const
            {
                std::vector<NodeCoordinates> adjacentCoordinates{};
                auto addCoordinate = [&adjacentCoordinates](const std::optional<NodeCoordinates>& coordinate)
                    {
                        if (coordinate.has_value())
                        {
                            adjacentCoordinates.push_back(coordinate.value());
                        }
                    };

                addCoordinate(left);
                addCoordinate(right);
                addCoordinate(forward);
                addCoordinate(backward);

                return adjacentCoordinates;
            }

            NodeCoordinates coordinates;
            std::optional<NodeCoordinates> left = std::nullopt;
            std::optional<NodeCoordinates> right = std::nullopt;
            std::optional<NodeCoordinates> forward = std::nullopt;
            std::optional<NodeCoordinates> backward = std::nullopt;
            Region* region = nullptr;
        };

        class Region
        {
        public:
            Region() = default;
            ~Region() = default;
            Region(const Region& other) = delete;
            Region& operator=(const Region& other) = delete;

            Region(NodePointer node)
            {
                node->region = this;
                addNode(node);
            }

            Region(Region&& other) noexcept : nodes(other.nodes)
            {
                updateNodesRegion();
            }

            Region& operator=(Region&& other) noexcept
            {
                nodes = other.nodes;
                updateNodesRegion();
                return *this;
            }

            void addNode(NodePointer node)
            {
                nodes.insert({ node->coordinates, std::move(node) });
            }

            void clearNodesRegion()
            {
                for (auto& [key, node] : nodes)
                {
                    node->region = nullptr;
                }
            }

            NodePointer getRandomNode() const
            {
                int randomIndex = math::Random::generateNumber(0, nodes.size());
                auto nodeIterator = std::next(begin(nodes), randomIndex);
                return nodeIterator->second;
            }

            bool hasNode(const NodeCoordinates& coordinates) const { return nodes.find(coordinates) != nodes.end(); }
            NodePointer getNode(const NodeCoordinates& coordinates) { return nodes[coordinates]; }
            NodePointer getNode(const NodeCoordinates& coordinates) const { return nodes.at(coordinates); }

            const NodeMap& getNodes() const { return nodes; }
            std::size_t getNodeCount() const { return nodes.size(); }

            void updateNodesRegion()
            {
                for (auto& [key, node] : nodes)
                {
                    node->region = this;
                }
            }

        private:
            NodeMap nodes{};
        };

        void addGridBounds(Grid& grid, int width, int height)
        {
            const int upperBound = height - 1;
            const int rightBound = width - 1;

            for (int x = 0; x < width; ++x)
            {
                grid[0][x] &= ~NodeValue::backward;
                grid[upperBound][x] &= ~NodeValue::forward;
            }

            for (int y = 0; y < width; ++y)
            {
                grid[y][0] &= ~NodeValue::left;
                grid[y][rightBound] &= ~NodeValue::right;
            }
        }

        Region getStartRegion(const Grid& grid, int width, int height)
        {
            Region region{};

            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    region.addNode(std::make_shared<Node>(x, y, width, height));
                }
            }

            return region;
        }

        std::tuple<Region, Region> plantSeed(Region& region, std::vector<NodePointer>& frontiers)
        {
            std::shared_ptr<Node> node = region.getRandomNode();
            frontiers.push_back(node);
            Region subRegion1(node);

            node = region.getRandomNode();
            frontiers.push_back(node);
            Region subRegion2(node);

            return { std::move(subRegion1), std::move(subRegion2) };
        }

        std::vector<NodePointer> getAdjacentNodes(const NodePointer& node, const Region& region)
        {
            std::vector<NodeCoordinates> adjacentCoordinates = node->getAdjacentNodeCoordinates();

            std::vector<NodePointer> adjacentNodes{};

            for (const NodeCoordinates& coordinate : adjacentCoordinates)
            {
                if (!region.hasNode(coordinate))
                {
                    continue;
                }

                NodePointer adjacentNode = region.getNode(coordinate);

                if (adjacentNode->region == nullptr)
                {
                    adjacentNodes.emplace_back(std::move(adjacentNode));
                }
            }

            return adjacentNodes;
        }

        std::vector<WallInfo> getWallInfo(const Region& region, const Region& subRegion)
        {
            std::vector<WallInfo> walls{};

            for (const auto& [key, node] : subRegion.getNodes())
            {
                auto tryAddWall = [&walls, &region, &node](const std::optional<NodeCoordinates>& coordinates, NodeValue direction)
                    {
                        if (coordinates.has_value() && region.hasNode(coordinates.value()))
                        {
                            if (node->region != region.getNode(coordinates.value())->region)
                            {
                                walls.emplace_back(WallInfo{ node->coordinates.x, node->coordinates.y, direction });
                            }
                        }
                    };

                tryAddWall(node->left, NodeValue::left);
                tryAddWall(node->right, NodeValue::right);
                tryAddWall(node->forward, NodeValue::forward);
                tryAddWall(node->backward, NodeValue::backward);
            }

            return walls;
        }

        void addWalls(const Region& region, const Region& subRegion, Grid& grid, MazeCallback* callback)
        {
            std::vector<WallInfo> walls = getWallInfo(region, subRegion);

            if (walls.empty())
            {
                return;
            }

            walls.erase(walls.begin() + math::Random::generateNumber(0, walls.size()));

            for (const WallInfo& wall : walls)
            {
                grid[wall.y][wall.x] &= ~wall.direction;
                auto [x, y] = getAdjacentCoordinates(wall.x, wall.y, wall.direction);
                grid[y][x] &= ~getOppositeNodeValue(wall.direction);

                if (callback)
                {
                    (*callback)(wall.x, wall.y, grid[wall.y][wall.x]);
                    (*callback)(x, y, grid[y][x]);
                }
            }
        }

        void addSubRegionToStack(std::stack<Region>& regions, Region& subRegion, int regionThreshold)
        {
            const bool greaterThanThreshold = subRegion.getNodeCount() >= regionThreshold;
            // Allows dividing a region that has less nodes than the threshold to sub regions
            const bool pushSmallRegion = subRegion.getNodeCount() >= minimumThreshold && math::Random::generateNumber(0, 10) < 5;

            if (greaterThanThreshold || pushSmallRegion)
            {
                regions.emplace(std::move(subRegion));
            }
            else
            {
                subRegion.updateNodesRegion();
            }
        }

        void blobbyDivision(int width, int height, int regionThreshold, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            Grid grid = generateGrid(width, height, NodeValue::left | NodeValue::right | NodeValue::forward | NodeValue::backward);
            addGridBounds(grid, width, height);
            std::stack<Region> regions{};
            std::vector<NodePointer> frontiers{};
            std::default_random_engine randomEngine{ math::Random::seed };
            regions.emplace(getStartRegion(grid, width, height));

            while (!regions.empty())
            {
                Region region = std::move(regions.top());
                regions.pop();
                region.clearNodesRegion();
                auto [subRegion1, subRegion2] = plantSeed(region, frontiers);

                while (!frontiers.empty())
                {
                    NodePointer node = frontiers.at(math::Random::generateNumber(0, frontiers.size()));

                    std::vector<NodePointer> adjacentNodes = getAdjacentNodes(node, region);

                    if (!adjacentNodes.empty())
                    {
                        NodePointer adjacentNode = adjacentNodes[math::Random::generateNumber(0, adjacentNodes.size())];
                        adjacentNode->region = node->region;
                        node->region->addNode(adjacentNode);
                        frontiers.push_back(adjacentNode);

                        if (!invokeAfterGeneration)
                        {
                            callback(node->coordinates.x, node->coordinates.y, grid[node->coordinates.y][node->coordinates.x]);
                            callback(adjacentNode->coordinates.x, adjacentNode->coordinates.y, grid[adjacentNode->coordinates.y][adjacentNode->coordinates.x]);
                        }
                    }
                    else
                    {
                        std::erase(frontiers, node);
                    }
                }

                addWalls(region, subRegion1, grid, invokeAfterGeneration ? nullptr : &callback);

                region.clearNodesRegion();
                addSubRegionToStack(regions, subRegion1, regionThreshold);
                addSubRegionToStack(regions, subRegion2, regionThreshold);
            }

            if (invokeAfterGeneration)
            {
                invokeCallback(grid, callback);
            }
        }
    }

    void blobbyDivision(int width, int height, bool invokeAfterGeneration, SubRegionSize regionSize, MazeCallback&& callback)
    {
        switch (regionSize)
        {
        case SubRegionSize::corridors:
            blobbyDivision(width, height, minimumThreshold, invokeAfterGeneration, std::move(callback));
            break;
        case SubRegionSize::small:
            blobbyDivision(width, height, smallThreshold, invokeAfterGeneration, std::move(callback));
            break;
        case SubRegionSize::medium:
            blobbyDivision(width, height, mediumThreshold, invokeAfterGeneration, std::move(callback));
            break;
        case SubRegionSize::large:
            blobbyDivision(width, height, largeThreshold, invokeAfterGeneration, std::move(callback));
            break;
        case SubRegionSize::huge:
            blobbyDivision(width, height, hugeThreshold, invokeAfterGeneration, std::move(callback));
            break;
        default:
            break;
        }

    }

    void blobbyDivision(int width, int height, bool invokeAfterGeneration, int regionThreshold, MazeCallback&& callback)
    {
        blobbyDivision(width, height, regionThreshold, invokeAfterGeneration, std::move(callback));
    }
}
