#ifndef PCG_ENGINE_MAZE_BINARY_TREE_HPP
#define PCG_ENGINE_MAZE_BINARY_TREE_HPP

#include <pcg/engine/maze/Common.hpp>
#include <pcg/engine/maze/Enums.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::maze
{
    namespace
    {
        template<typename addMazePointCallback>
        void binaryTree(int width, int height, std::vector<int> directions, addMazePointCallback callback)
        {
            std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));
            auto randomDevice = std::random_device{};
            auto randomEngine = std::default_random_engine{ randomDevice() };

            for (int h = 0; h < height; ++h)
            {
                for (int w = 0; w < width; ++w)
                {
                    std::shuffle(begin(directions), end(directions), randomEngine);

                    for (int direction : directions)
                    {
                        auto [nw, nh] = getNeighborXY(w, h, direction);

                        if (nw >= 0 && nh >= 0 && nw < width && nh < height)
                        {
                            grid[h][w] |= direction;
                            grid[nh][nw] |= getFlippedDirection(direction);
                            std::ostringstream oss{};
                            oss << "Value set at " << w << "-" << h << "/" << nw << "-" << nh;
                            utility::logInfo(oss.str());
                            callback(w, h, grid[h][w]);
                            callback(nw, nh, grid[nh][nw]);
                            break;
                        }
                    }
                }
            }
        }
    }

    template<typename addMazePointCallback>
    void binaryTree(int width, int height, Diagonal diagonal, addMazePointCallback callback)
    {
        switch (diagonal)
        {
        case Diagonal::NE:
        {
            utility::logInfo("Binary Tree NE Maze Generation Started");
            binaryTree(width, height, { up, right }, callback);
            utility::logInfo("Binary Tree NE Maze Generation Ended");
            break;
        }
        case Diagonal::NW:
        {
            utility::logInfo("Binary Tree NW Maze Generation Started");
            binaryTree(width, height, { up, left }, callback);
            utility::logInfo("Binary Tree NW Maze Generation Ended");
            break;
        }
        case Diagonal::SE:
        {
            utility::logInfo("Binary Tree SE Maze Generation Started");
            binaryTree(width, height, { down, right }, callback);
            utility::logInfo("Binary Tree SE Maze Generation Ended");
            break;
        }
        case Diagonal::SW:
        {
            utility::logInfo("Binary Tree SW Maze Generation Started");
            binaryTree(width, height, { down, left }, callback);
            utility::logInfo("Binary Tree SW Maze Generation Ended");
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

#endif // PCG_ENGINE_MAZE_BINARY_TREE_HPP
