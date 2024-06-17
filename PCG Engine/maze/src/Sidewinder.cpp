#include <pcg/engine/maze/Sidewinder.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <sstream>

namespace pcg::engine::maze
{
    void sidewinder(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
    {
        utility::logInfo("Sidewinder Maze Generation Started");

        Grid grid = generateGrid(width, height);

        for (std::size_t h = 0; h < height; ++h)
        {
            std::size_t runStart = 0;

            for (std::size_t w = 0; w < width; ++w)
            {
                if (h > 0 && (w + 1 == width || math::Random::generate(0, 2) == 0))
                {
                    utility::logInfo("Ending run and carving north");
                    int cell = math::Random::generate(runStart, w + 1);
                    grid[h][cell] |= utility::enums::Direction::backward;
                    grid[h - 1][cell] |= utility::enums::Direction::forward;
                    runStart = w + 1;
                    std::ostringstream oss{};
                    oss << "Value set at " << cell << "-" << h << "/" << cell << "-" << h - 1;
                    utility::logInfo(oss.str());

                    if (!invokeAfterGeneration)
                    {
                        callback(cell, h, grid[h][cell]);
                        callback(cell, h - 1, grid[h - 1][cell]);
                    }
                }
                else if (w + 1 < width)
                {
                    utility::logInfo("Carving east");
                    grid[h][w] |= utility::enums::Direction::right;
                    grid[h][w + 1] |= utility::enums::Direction::left;
                    std::ostringstream oss{};
                    oss << "Value set at " << w << "-" << h << "/" << w + 1 << "-" << h;
                    utility::logInfo(oss.str());

                    if (!invokeAfterGeneration)
                    {
                        callback(w, h, grid[h][w]);
                        callback(w + 1, h, grid[h][w + 1]);
                    }
                }
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

        utility::logInfo("Sidewinder Maze Generation Started");
    }
}
