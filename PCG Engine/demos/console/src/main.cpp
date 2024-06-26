#include <pcg/engine/cpp-api/api.hpp>

#include <pcg/engine/maze-generation/RecursiveDivision.hpp>

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
    simpleGeneration(data, Axis::negativeX, addPoints);

    std::cout << "2D Generation" << std::endl;
    multiDimensionGeneration(data, Axis::yz, true, addPoints);

    std::cout << "3D Generation" << std::endl;
    multiDimensionGeneration(data, Axis::xyz, true, addPoints);

    std::cout << "Wave Function Collapse DFS" << std::endl;
    data.count = 115;
    waveFunctionCollapseGeneration(data, ExpansionMode::DFS, Axis::xz, addWFCPoints);
    std::cout << "Wave Function Collapse BFS" << std::endl;
    waveFunctionCollapseGeneration(data, ExpansionMode::BFS, Axis::xz, addWFCPoints);

    std::cout << "Maze Generation: aldousBroder" << std::endl;
    generateMaze(width, height, true, MazeAlgorithm::aldousBroder, addMazePoint);

    std::cout << "Maze Generation: wilson" << std::endl;
    generateMaze(width, height, true, MazeAlgorithm::wilson, addMazePoint);

    std::cout << "Maze Generation: Binary Tree NE" << std::endl;
    generateMaze(width, height, true, MazeAlgorithm::binaryTreeNE, addMazePoint);

    std::cout << "Maze Generation: sidewinder" << std::endl;
    generateMaze(width, height, true, MazeAlgorithm::sidewinder, addMazePoint);

    std::cout << "Maze Generation: Recursive Division" << std::endl;
    generateMaze(width, height, true, MazeAlgorithm::recursiveDivision, addMazePoint);

    constexpr bool hasXY = pcg::engine::utility::enums::hasFlag(Axis::xy, Axis::x, Axis::y);
    constexpr bool hasXYZ = pcg::engine::utility::enums::hasFlag(Axis::xy, Axis::x, Axis::y, Axis::z);

    std::cout << "XY has x y: " << hasXY << std::endl;
    std::cout << "XY has x y z: " << hasXYZ << std::endl;

    const std::vector<std::string> colors{ "Red", "Green", "Blue", "Purple", "Yellow", "Pink" };
    auto combinationCallback = [&colors](int index, bool included)
        {
            if (included)
            {
                std::cout << colors[index] << " included in set" << std::endl;
            }
        };

    std::cout << "Generate Combination:" << std::endl;
    pcg::engine::cpp_api::generateCombination(colors.size(), combinationCallback);

    std::cout << "Generate Combination with minimum of 3 elements:" << std::endl;
    pcg::engine::cpp_api::generateCombination(colors.size(), 3, combinationCallback);

    std::cout << "Generate Combination with minimum of Blue and Pink:" << std::endl;
    pcg::engine::cpp_api::generateCombination(colors.size(), { 2, 5 }, combinationCallback);

    std::cout << "Generate Combination with minimum of Red, Green and Pink:" << std::endl;
    pcg::engine::cpp_api::generateCombination(colors.size(), { 0, 1, 5 }, combinationCallback);

    pcg::engine::cpp_api::setRandomGenerator(nullptr, nullptr);

    return 0;
}
