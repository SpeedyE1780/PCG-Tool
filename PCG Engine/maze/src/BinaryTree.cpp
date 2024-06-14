#include <pcg/engine/maze/BinaryTree.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <random>
#include <sstream>

namespace pcg::engine::maze
{
    namespace
    {
        void binaryTree(int width, int height, std::vector<int> directions, utility::CallbackFunctor<int, int, int>&& callback)
        {
            grid grid = generateGrid(width, height);
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

    void binaryTree(int width, int height, Diagonal diagonal, utility::CallbackFunctor<int, int, int>&& callback)
    {
        switch (diagonal)
        {
        case Diagonal::NE:
        {
            utility::logInfo("Binary Tree NE Maze Generation Started");
            binaryTree(width, height, { up, right }, std::move(callback));
            utility::logInfo("Binary Tree NE Maze Generation Ended");
            break;
        }
        case Diagonal::NW:
        {
            utility::logInfo("Binary Tree NW Maze Generation Started");
            binaryTree(width, height, { up, left }, std::move(callback));
            utility::logInfo("Binary Tree NW Maze Generation Ended");
            break;
        }
        case Diagonal::SE:
        {
            utility::logInfo("Binary Tree SE Maze Generation Started");
            binaryTree(width, height, { down, right }, std::move(callback));
            utility::logInfo("Binary Tree SE Maze Generation Ended");
            break;
        }
        case Diagonal::SW:
        {
            utility::logInfo("Binary Tree SW Maze Generation Started");
            binaryTree(width, height, { down, left }, std::move(callback));
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
