#include <pcg/engine/maze/Sidewinder.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <sstream>

namespace pcg::engine::maze
{
    void sidewinder(int width, int height, MazeCallback&& callback)
    {
        utility::logInfo("Sidewinder Maze Generation Started");

        grid grid = generateGrid(width, height);

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
