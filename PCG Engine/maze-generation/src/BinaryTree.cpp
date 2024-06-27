#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/BinaryTree.hpp>
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
        void binaryTree(int width, int height, bool invokeAfterGeneration, std::vector<utility::enums::Direction>&& directions, MazeCallback&& callback)
        {
            Grid grid = generateGrid(width, height);
            auto randomEngine = std::default_random_engine{ math::Random::seed };

            for (int h = 0; h < height; ++h)
            {
                for (int w = 0; w < width; ++w)
                {
                    std::shuffle(begin(directions), end(directions), randomEngine);

                    for (utility::enums::Direction direction : directions)
                    {
                        auto [nw, nh] = getAdjacentCoordinates(w, h, direction);

                        if (nw >= 0 && nh >= 0 && nw < width && nh < height)
                        {
                            grid[h][w] |= direction;
                            grid[nh][nw] |= utility::enums::getFlippedDirection(direction);
                            std::ostringstream oss{};
                            oss << "Value set at " << w << "-" << h << "/" << nw << "-" << nh;
                            utility::logInfo(oss.str());

                            if (!invokeAfterGeneration)
                            {
                                callback(w, h, grid[h][w]);
                                callback(nw, nh, grid[nh][nw]);
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
            binaryTree(width, height, invokeAfterGeneration, { utility::enums::Direction::forward, utility::enums::Direction::right }, std::move(callback));
            utility::logInfo("Binary Tree NE Maze Generation Ended");
            break;
        }
        case Diagonal::NW:
        {
            utility::logInfo("Binary Tree NW Maze Generation Started");
            binaryTree(width, height, invokeAfterGeneration, { utility::enums::Direction::forward, utility::enums::Direction::left }, std::move(callback));
            utility::logInfo("Binary Tree NW Maze Generation Ended");
            break;
        }
        case Diagonal::SE:
        {
            utility::logInfo("Binary Tree SE Maze Generation Started");
            binaryTree(width, height, invokeAfterGeneration, { utility::enums::Direction::backward, utility::enums::Direction::right }, std::move(callback));
            utility::logInfo("Binary Tree SE Maze Generation Ended");
            break;
        }
        case Diagonal::SW:
        {
            utility::logInfo("Binary Tree SW Maze Generation Started");
            binaryTree(width, height, invokeAfterGeneration, { utility::enums::Direction::backward, utility::enums::Direction::left }, std::move(callback));
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
