#include <pcg/engine/level-generation/node.hpp>

#include <pcg/engine/cpp-api/api.hpp>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace pcg::engine::level_generation;
using namespace pcg::engine::cpp_api;
using namespace pcg::engine::math;
using namespace pcg::engine::maze;

namespace
{
    constexpr int width = 10;
    constexpr int height = 10;

    std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));

    void addPoints(Vector3 point)
    {
        std::cout << "Point:" << point.x << "," << point.y << "," << point.z << std::endl;
    }

    void addWFCPoints(Vector3 point, int neighbors)
    {
        std::cout << "Point:" << point.x << "," << point.y << "," << point.z << std::endl;
        std::cout << "Neighbors: ";

        if (neighbors & Neighbors::left)
        {
            std::cout << "L";
        }

        if (neighbors & Neighbors::right)
        {
            std::cout << "R";
        }

        if (neighbors & Neighbors::forward)
        {
            std::cout << "F";
        }

        if (neighbors & Neighbors::backward)
        {
            std::cout << "B";
        }

        if (neighbors & Neighbors::up)
        {
            std::cout << "U";
        }

        if (neighbors & Neighbors::down)
        {
            std::cout << "D";
        }

        std::cout << std::endl;
    }

    void addMazePoint(int x, int y, int neighbor)
    {
        grid[y][x] = neighbor;
    }

    void logMessage(const char* message)
    {
        std::cout << message << std::endl;
    }
}

int main()
{
    setLoggingFunction(logMessage);

    std::cout << "Simple Generation" << std::endl;
    GenerationData data{ 10, 1, { 0, 0, 0 } };
    simpleGeneration(&data, axis::x, Direction::negative, addPoints);

    std::cout << "2D Generation" << std::endl;
    multiDimensionGeneration(&data, axis::yz, true, addPoints);

    std::cout << "3D Generation" << std::endl;
    multiDimensionGeneration(&data, axis::x | axis::y | axis::z, true, addPoints);

    std::cout << "Wave Function Collapse DFS" << std::endl;
    data.limit = 115;
    waveFunctionCollapseGeneration(&data, ExpansionMode::DFS, pcg::engine::math::axis::xz, addWFCPoints);
    std::cout << "Wave Function Collapse BFS" << std::endl;
    waveFunctionCollapseGeneration(&data, ExpansionMode::BFS, pcg::engine::math::axis::xz, addWFCPoints);

    std::cout << "Maze Generation: aldousBroder" << std::endl;
    generateMaze(width, height, MazeAlgorithm::aldousBroder, addMazePoint);

    std::cout << "Maze Generation: wilson" << std::endl;
    generateMaze(width, height, MazeAlgorithm::wilson, addMazePoint);

    std::cout << "Maze Generation: Binary Tree NE" << std::endl;
    generateMaze(width, height, MazeAlgorithm::binaryTreeNE, addMazePoint);

    std::cout << "Maze Generation: sidewinder" << std::endl;
    generateMaze(width, height, MazeAlgorithm::sidewinder, addMazePoint);

    int x = 0;
    int y = 0;

    for (const auto& row : grid)
    {
        for (int point : row)
        {
            std::cout << x << "-" << y << ": " << point << std::endl;
            x += 1;
        }

        y += 1;
        x = 0;
    }

    return 0;
}
