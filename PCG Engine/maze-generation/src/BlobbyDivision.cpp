#include <pcg/engine/maze-generation/BlobbyDivision.hpp>

#include <pcg/engine/math/random.hpp>

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
        struct NodeCoordinates
        {
            NodeCoordinates(std::tuple<int, int>&& coordinates) : x(std::get<0>(coordinates)), y(std::get<1>(coordinates))
            {
            }

            int x;
            int y;
        };

        bool operator==(const NodeCoordinates& lhs, const NodeCoordinates& rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
    }
}

namespace std
{
    template<>
    struct hash<pcg::engine::maze_generation::NodeCoordinates>
    {
        std::size_t operator()(const pcg::engine::maze_generation::NodeCoordinates& value) const
        {
            const auto& [x, y] = value;
            std::size_t xHash = std::hash<int>{}(x);
            std::size_t yHash = std::hash<int>{}(y);

            return xHash ^ (yHash << 1);
        }
    };
}

namespace pcg::engine::maze_generation
{
    namespace
    {
        struct Node;
        class Region;
        using NodePointer = std::shared_ptr<Node>;
        using NodeMap = std::unordered_map<NodeCoordinates, NodePointer>;

        struct WallInfo
        {
            int x;
            int y;
            utility::enums::Direction direction;
        };

        struct Node
        {
            Node(int x, int y, int width, int height) : coordinates({ x, y })
            {
                if (x > 0)
                {
                    left = getAdjacentCoordinates(x, y, utility::enums::Direction::left);
                }

                if (x < width - 1)
                {
                    right = getAdjacentCoordinates(x, y, utility::enums::Direction::right);
                }

                if (y > 0)
                {
                    backward = getAdjacentCoordinates(x, y, utility::enums::Direction::backward);
                }

                if (y < height - 1)
                {
                    forward = getAdjacentCoordinates(x, y, utility::enums::Direction::forward);
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
                grid[0][x] &= ~utility::enums::Direction::backward;
                grid[upperBound][x] &= ~utility::enums::Direction::forward;
            }

            for (int y = 0; y < width; ++y)
            {
                grid[y][0] &= ~utility::enums::Direction::left;
                grid[y][rightBound] &= ~utility::enums::Direction::right;
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
                auto tryAddWall = [&walls, &region, &node](const std::optional<NodeCoordinates>& coordinates, utility::enums::Direction direction)
                    {
                        if (coordinates.has_value() && region.hasNode(coordinates.value()))
                        {
                            if (node->region != region.getNode(coordinates.value())->region)
                            {
                                walls.emplace_back(WallInfo{ node->coordinates.x, node->coordinates.y, direction });
                            }
                        }
                    };

                tryAddWall(node->left, utility::enums::Direction::left);
                tryAddWall(node->right, utility::enums::Direction::right);
                tryAddWall(node->forward, utility::enums::Direction::forward);
                tryAddWall(node->backward, utility::enums::Direction::backward);
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
                grid[y][x] &= ~utility::enums::getFlippedDirection(wall.direction);

                if (callback)
                {
                    (*callback)(wall.x, wall.y, grid[wall.y][wall.x]);
                    (*callback)(x, y, grid[y][x]);
                }
            }
        }
    }

    void pcg::engine::maze_generation::blobbyDivision(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        Grid grid = generateGrid(width, height, utility::enums::Direction::left | utility::enums::Direction::right | utility::enums::Direction::forward | utility::enums::Direction::backward);
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
                }
                else
                {
                    std::erase(frontiers, node);
                }
            }

            addWalls(region, subRegion1, grid, invokeAfterGeneration ? nullptr : &callback);

            region.clearNodesRegion();

            if (subRegion1.getNodeCount() > 4)
            {
                regions.emplace(std::move(subRegion1));
            }
            else
            {
                subRegion1.updateNodesRegion();
            }

            if (subRegion2.getNodeCount() > 4)
            {
                regions.emplace(std::move(subRegion2));
            }
            else
            {
                subRegion2.updateNodesRegion();
            }
        }

        if (invokeAfterGeneration)
        {
            for (int y = 0; y < grid.size(); ++y)
            {
                for (int x = 0; x < grid[0].size(); ++x)
                {
                    callback(x, y, grid[y][x]);
                }
            }
        }
    }
}
