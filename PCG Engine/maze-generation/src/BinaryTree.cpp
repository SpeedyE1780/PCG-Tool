#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/BinaryTree.hpp>
#include <pcg/engine/maze-generation/NodeCoordinates.hpp>
#include <pcg/engine/maze-generation/Utility.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <random>
#include <sstream>

namespace pcg::engine::maze_generation
{
    namespace
    {
        /// @brief Geneate maze using Binary Tree Algorithm
        /// @param width Grid Width
        /// @param height Grid Height
        /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
        /// @param directions Vector containing the N/S and W/E pair of direction
        /// @param callback Callback when a node is generated
        void binaryTree(int width, int height, bool invokeAfterGeneration, std::vector<NodeValue>&& directions, MazeCallback&& callback)
        {
            Grid grid = generateGrid(width, height);
            auto randomEngine = std::default_random_engine{ math::Random::seed };

            for (int h = 0; h < height; ++h)
            {
                for (int w = 0; w < width; ++w)
                {
                    std::shuffle(begin(directions), end(directions), randomEngine);

                    for (NodeValue direction : directions)
                    {
                        auto [nw, nh] = getAdjacentCoordinates(w, h, direction);

                        if (isWithinGridBounds(nw, nh, width, height))
                        {
                            grid[h][w] |= direction;
                            grid[nh][nw] |= getOppositeNodeValue(direction);
                            std::ostringstream oss{};
                            oss << "Value set at " << w << "-" << h << "/" << nw << "-" << nh;
                            utility::logInfo(oss.str());

                            if (!invokeAfterGeneration)
                            {
                                invokeNodePairCallback(w, h, nw, nh, grid, callback);
                            }

                            break;
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

    void binaryTree(int width, int height, bool invokeAfterGeneration, Diagonal diagonal, MazeCallback&& callback)
    {
        switch (diagonal)
        {
        case Diagonal::NE:
        {
            utility::logInfo("Binary Tree NE Maze Generation Started");
            binaryTree(width, height, invokeAfterGeneration, { NodeValue::forward, NodeValue::right }, std::move(callback));
            utility::logInfo("Binary Tree NE Maze Generation Ended");
            break;
        }
        case Diagonal::NW:
        {
            utility::logInfo("Binary Tree NW Maze Generation Started");
            binaryTree(width, height, invokeAfterGeneration, { NodeValue::forward, NodeValue::left }, std::move(callback));
            utility::logInfo("Binary Tree NW Maze Generation Ended");
            break;
        }
        case Diagonal::SE:
        {
            utility::logInfo("Binary Tree SE Maze Generation Started");
            binaryTree(width, height, invokeAfterGeneration, { NodeValue::backward, NodeValue::right }, std::move(callback));
            utility::logInfo("Binary Tree SE Maze Generation Ended");
            break;
        }
        case Diagonal::SW:
        {
            utility::logInfo("Binary Tree SW Maze Generation Started");
            binaryTree(width, height, invokeAfterGeneration, { NodeValue::backward, NodeValue::left }, std::move(callback));
            utility::logInfo("Binary Tree SW Maze Generation Ended");
            break;
        }
        default:
        {
            utility::logError("Invalid Diagonal passed to binaryTree");
            break;
        }
        }
    }
}
