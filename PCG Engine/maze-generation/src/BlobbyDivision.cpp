#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/BlobbyDivision.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

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
        /// @brief Threshold used with SubRegionSize::small
        constexpr int smallThreshold = 10;
        /// @brief Threshold used with SubRegionSize::medium
        constexpr int mediumThreshold = 25;
        /// @brief Threshold used with SubRegionSize::large
        constexpr int largeThreshold = 40;
        /// @brief Threshold used with SubRegionSize::huge
        constexpr int hugeThreshold = 70;

        /// @brief WallInfo contains wall coordinates and direction
        struct WallInfo
        {
            int x;
            int y;
            NodeValue direction;
        };

        /// @brief Represents a node in a region
        struct Node
        {
            /// @brief Construct a node and assign its adjacent nodes
            /// @param x X coordinate
            /// @param y Y coordinate
            /// @param width Grid Width
            /// @param height Grid Height
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

            /// @brief Get adjacent nodes in region
            /// @param region Region that nodes should belong to
            /// @return All adjacent nodes in region
            std::vector<NodeCoordinates> getAdjacentNodeCoordinates(std::function<bool(NodeCoordinates)>&& regionHasNode) const
            {
                std::vector<NodeCoordinates> adjacentCoordinates{};
                auto addCoordinate = [&adjacentCoordinates, &regionHasNode](const std::optional<NodeCoordinates>& coordinate)
                    {
                        if (coordinate.has_value() && regionHasNode(coordinate.value()))
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

            /// @brief Node coordinates in grid
            NodeCoordinates coordinates;
            /// @brief Region this node belongs to
            Region* region = nullptr;
            /// @brief Left adjacent node if it exists
            std::optional<NodeCoordinates> left = std::nullopt;
            /// @brief Rigt adjacent node if it exists
            std::optional<NodeCoordinates> right = std::nullopt;
            /// @brief Forward adjacent node if it exists
            std::optional<NodeCoordinates> forward = std::nullopt;
            /// @brief Backward adjacent node if it exists
            std::optional<NodeCoordinates> backward = std::nullopt;
        };

        /// @brief Region is a collection of nodes that belong to the same region
        class Region
        {
        public:
            Region() = default;
            ~Region() = default;
            Region(const Region& other) = delete;
            Region& operator=(const Region& other) = delete;

            /// @brief Construct region and assign the seed
            /// @param node The seed of this region
            Region(NodePointer node) : seed(node)
            {
                seed->region = this;
                addNode(seed);
            }

            Region(Region&& other) noexcept : nodes(other.nodes), seed(other.seed)
            {
                updateNodesRegion();
            }

            Region& operator=(Region&& other) noexcept
            {
                nodes = other.nodes;
                updateNodesRegion();
                return *this;
            }

            /// @brief Add node to region
            /// @param node Node added to region
            void addNode(NodePointer node)
            {
                nodes.insert({ node->coordinates, std::move(node) });
            }

            /// @brief Reset region of all nodes in region
            void clearNodesRegion()
            {
                for (auto& [key, node] : nodes)
                {
                    node->region = nullptr;
                }
            }

            /// @brief Get Random node in region
            /// @return Random node in region
            NodePointer getRandomNode() const
            {
                int randomIndex = math::Random::number(nodes.size());
                auto nodeIterator = std::next(begin(nodes), randomIndex);
                return nodeIterator->second;
            }

            /// @brief Check if region contains node
            /// @param coordinates Node coordinates
            /// @return True if regions contains node
            bool hasNode(const NodeCoordinates& coordinates) const { return nodes.find(coordinates) != nodes.end(); }
            /// @brief Get node at coordinate
            /// @param coordinates Node Coordinates
            /// @return Node
            NodePointer getNode(const NodeCoordinates& coordinates) { return nodes[coordinates]; }
            /// @brief Get node at coordinate
            /// @param coordinates Node Coordinates
            /// @return Node
            NodePointer getNode(const NodeCoordinates& coordinates) const { return nodes.at(coordinates); }
            /// @brief Get Region Seed
            /// @return Region Seed
            NodePointer getSeed() { return seed; }
            /// @brief Get Region Seed
            /// @return Region Seed
            NodePointer getSeed() const { return seed; }

            /// @brief Get all nodes in region
            /// @return Nodes in region
            const NodeMap& getNodes() const { return nodes; }
            /// @brief Get node count in region
            /// @return Node count in region
            std::size_t getNodeCount() const { return nodes.size(); }

            /// @brief Update all nodes' region to this
            void updateNodesRegion()
            {
                for (auto& [key, node] : nodes)
                {
                    node->region = this;
                }
            }

        private:
            /// @brief Map of nodes belonging to region
            NodeMap nodes{};
            /// @brief Seed of this region
            NodePointer seed = nullptr;
        };

        /// @brief Get Region that contains all nodes in the maze
        /// @param grid Grid representing maze
        /// @param width Grid width
        /// @param height Grid height
        /// @return Region that contains all nodes in the maze
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

        /// @brief Divide region in two sub regions and assign a seed for each sub region
        /// @param region Region being divided in two
        /// @return The two new sub regions
        std::tuple<Region, Region> plantSeed(Region& region)
        {
            utility::logInfo("Planting seeds in region");
            return { Region(region.getRandomNode()), Region(region.getRandomNode()) };
        }

        /// @brief Get all adjacent nodes that share the same region as node
        /// @param node Current node
        /// @param region Region the nodes belong to
        /// @return All adjacent nodes that share the same region as node
        std::vector<NodePointer> getAdjacentNodes(const NodePointer& node, const Region& region)
        {
            std::vector<NodeCoordinates> adjacentCoordinates = node->getAdjacentNodeCoordinates([&region](const NodeCoordinates& coordinates)
                {
                    return region.hasNode(coordinates);
                });

            std::vector<NodePointer> adjacentNodes{};

            for (const NodeCoordinates& coordinate : adjacentCoordinates)
            {
                if (NodePointer adjacentNode = region.getNode(coordinate); adjacentNode->region == nullptr)
                {
                    adjacentNodes.emplace_back(std::move(adjacentNode));
                }
            }

            return adjacentNodes;
        }

        /// @brief Grow subregions until all nodes are assigned a sub region
        /// @param region Region containing the two sub regions
        /// @param frontiers Vector containing the seeds of the two sub regions
        /// @param grid Grid representing maze
        /// @param callback User defined callback nullptr if callback should be invoked after maze generation
        void growSubRegions(Region& region, std::vector<NodePointer>&& frontiers, Grid& grid, MazeCallback* callback)
        {
            utility::logInfo("Growing sub regions");

            while (!frontiers.empty())
            {
                NodePointer node = frontiers.at(math::Random::number(frontiers.size()));

                if (std::vector<NodePointer> adjacentNodes = getAdjacentNodes(node, region); !adjacentNodes.empty())
                {
                    NodePointer adjacentNode = adjacentNodes[math::Random::number(adjacentNodes.size())];
                    adjacentNode->region = node->region;
                    node->region->addNode(adjacentNode);
                    frontiers.push_back(adjacentNode);

                    if (callback)
                    {
                        invokeNodePairCallback(node->coordinates.x, node->coordinates.y,
                            adjacentNode->coordinates.x, adjacentNode->coordinates.y,
                            grid, *callback);
                    }
                }
                else
                {
                    std::erase(frontiers, node);
                }
            }
        }

        /// @brief Get sub region wall info vector
        /// @param region Region containing the two sub regions
        /// @param subRegion Sub region used to find borders between the two sub regions
        /// @return Sub region wall info vector
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

        /// @brief Loop over nodes in subregion and add walls between node that doesn't share the same region
        /// @param region Region containing the two sub regions
        /// @param subRegion Sub region used to find borders between the two sub regions
        /// @param grid Grid representing maze
        /// @param callback User defined callback nullptr if callback should be invoked after maze generation
        void addWalls(const Region& region, const Region& subRegion, Grid& grid, MazeCallback* callback)
        {
            utility::logInfo("Adding walls seperation between regions");
            std::vector<WallInfo> walls = getWallInfo(region, subRegion);

            if (walls.empty())
            {
                return;
            }

            walls.erase(walls.begin() + math::Random::number(walls.size()));

            for (const WallInfo& wall : walls)
            {
                auto [x, y] = getAdjacentCoordinates(wall.x, wall.y, wall.direction);
                addAdjacentNodeWall(wall.x, wall.y, x, y, wall.direction, grid);

                if (callback)
                {
                    invokeNodePairCallback(wall.x, wall.y, x, y, grid, *callback);
                }
            }
        }

        /// @brief Add subregion to stack if it has more nodes than the threshold
        /// @param regions Regions Stack
        /// @param subRegion Sub Region being added
        /// @param regionThreshold Minimum node count to divide region
        void addSubRegionToStack(std::stack<Region>& regions, Region& subRegion, int regionThreshold)
        {
            const bool greaterThanThreshold = subRegion.getNodeCount() >= regionThreshold;
            // Allows dividing a region that has less nodes than the threshold to sub regions
            const bool pushSmallRegion = subRegion.getNodeCount() >= minimumThreshold && math::Random::boolean(10, 5);

            if (greaterThanThreshold || pushSmallRegion)
            {
                utility::logInfo("Adding region to stack");
                regions.emplace(std::move(subRegion));
            }
            else
            {
                utility::logInfo("Region can't be divided further");
                subRegion.updateNodesRegion();
            }
        }

        /// @brief Add sub regions to stack if they can be divided into subregions
        /// @param regions Regions Stack
        /// @param subRegion1 First sub region
        /// @param subRegion2 Second sub region
        /// @param regionThreshold Minimum node count to divide region
        void addSubRegionsToStack(std::stack<Region>& regions, Region& subRegion1, Region& subRegion2, int regionThreshold)
        {
            addSubRegionToStack(regions, subRegion1, regionThreshold);
            addSubRegionToStack(regions, subRegion2, regionThreshold);
        }

        /// @brief Divide region in two sub regions
        /// @param region Region being divided
        /// @param grid Grid representing maze
        /// @param callback User defined callback nullptr if callback should be invoked after maze generation
        /// @return The two new sub regions
        std::tuple<Region, Region> divideRegion(Region& region, Grid& grid, MazeCallback* callback)
        {
            auto [subRegion1, subRegion2] = plantSeed(region);
            growSubRegions(region, { subRegion1.getSeed(), subRegion2.getSeed() }, grid, callback);
            addWalls(region, subRegion1, grid, callback);
            return { std::move(subRegion1), std::move(subRegion2) };
        }

        /// @brief Generate Maze using Blobby Division
        /// @param width Grid Width
        /// @param height Grid Height
        /// @param regionThreshold Region node count threshold
        /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
        /// @param callback Callback when a node is generated
        void blobbyDivision(int width, int height, int regionThreshold, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            utility::logInfo("Blobby Division Maze Generation Started");

            Grid grid = generateOpenGrid(width, height);
            std::stack<Region> regions{};
            regions.emplace(getStartRegion(grid, width, height));

            while (!regions.empty())
            {
                Region region = std::move(regions.top());
                regions.pop();
                region.clearNodesRegion();
                auto [subRegion1, subRegion2] = divideRegion(region, grid, invokeAfterGeneration ? nullptr : &callback);
                region.clearNodesRegion();
                addSubRegionsToStack(regions, subRegion1, subRegion2, regionThreshold);
            }

            if (invokeAfterGeneration)
            {
                invokeCallback(grid, callback);
            }

            utility::logInfo("Blobby Division Maze Generation Ended");
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
