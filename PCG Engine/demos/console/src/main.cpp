#include <pcg/engine/level-generation/node.hpp>

#include <pcg/engine/cpp-api/api.hpp>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace pcg::engine::level_generation;
using namespace pcg::engine::cpp_api;
using namespace pcg::engine::math;

namespace
{
    constexpr int width = 10;
    constexpr int height = 10;

    void addPoints(Vector3 point)
    {
        std::cout << "Point:" << point.x << "," << point.y << "," << point.z << std::endl;
    }

    void addWFCPoints(Vector3 point, pcg::engine::utility::enums::Direction neighbors)
    {
        std::cout << "Point:" << point.x << "," << point.y << "," << point.z << std::endl;
        std::cout << "Neighbors: ";

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::left))
        {
            std::cout << "L";
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::right))
        {
            std::cout << "R";
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::forward))
        {
            std::cout << "F";
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::backward))
        {
            std::cout << "B";
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::up))
        {
            std::cout << "U";
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::down))
        {
            std::cout << "D";
        }

        std::cout << std::endl;
    }

    void addMazePoint(int x, int y, pcg::engine::utility::enums::Direction neighbor)
    {
        std::cout << "Point: " << x << "-" << y << " value: " << static_cast<int>(neighbor) << std::endl;
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
    simpleGeneration(&data, Axis::x, Direction::negative, addPoints);

    std::cout << "2D Generation" << std::endl;
    multiDimensionGeneration(&data, Axis::yz, true, addPoints);

    std::cout << "3D Generation" << std::endl;
    multiDimensionGeneration(&data, Axis::xyz, true, addPoints);

    std::cout << "Wave Function Collapse DFS" << std::endl;
    data.limit = 115;
    waveFunctionCollapseGeneration(&data, ExpansionMode::DFS, Axis::xz, addWFCPoints);
    std::cout << "Wave Function Collapse BFS" << std::endl;
    waveFunctionCollapseGeneration(&data, ExpansionMode::BFS, Axis::xz, addWFCPoints);

    std::cout << "Maze Generation: aldousBroder" << std::endl;
    generateMaze(width, height, true, MazeAlgorithm::aldousBroder, addMazePoint);

    std::cout << "Maze Generation: wilson" << std::endl;
    generateMaze(width, height, true, MazeAlgorithm::wilson, addMazePoint);

    std::cout << "Maze Generation: Binary Tree NE" << std::endl;
    generateMaze(width, height, true, MazeAlgorithm::binaryTreeNE, addMazePoint);

    std::cout << "Maze Generation: sidewinder" << std::endl;
    generateMaze(width, height, true, MazeAlgorithm::sidewinder, addMazePoint);

    return 0;
}
