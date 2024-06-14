#include <pcg/engine/maze/Common.hpp>
#include <pcg/engine/maze/Maze.hpp>

#include <pcg/engine/math/random.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <map>
#include <random>
#include <sstream>
#include <vector>

namespace pcg::engine::maze
{
    namespace
    {
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

    void sidewinder(int width, int height, addMazePointCallback callback)
    {
        utility::logInfo("Sidewinder Maze Generation Started");

        std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));

        for (std::size_t h = 0; h < height; ++h)
        {
            std::size_t runStart = 0;

            for (std::size_t w = 0; w < width; ++w)
            {
                if (h > 0 && (w + 1 == width || math::Random::generate(0, 2) == 0))
                {
                    utility::logInfo("Ending run and carving north");
                    int cell = math::Random::generate(runStart, w + 1);
                    grid[h][cell] |= down;
                    grid[h - 1][cell] |= up;
                    runStart = w + 1;
                    std::ostringstream oss{};
                    oss << "Value set at " << cell << "-" << h << "/" << cell << "-" << h - 1;
                    utility::logInfo(oss.str());
                    callback(cell, h, grid[h][cell]);
                    callback(cell, h - 1, grid[h - 1][cell]);
                }
                else if (w + 1 < width)
                {
                    utility::logInfo("Carving east");
                    grid[h][w] |= right;
                    grid[h][w + 1] |= left;
                    std::ostringstream oss{};
                    oss << "Value set at " << w << "-" << h << "/" << w + 1 << "-" << h;
                    utility::logInfo(oss.str());
                    callback(w, h, grid[h][w]);
                    callback(w + 1, h, grid[h][w + 1]);
                }
            }
        }

        utility::logInfo("Sidewinder Maze Generation Started");
    }
}
