#include <iostream>>
#include <pcg/engine/core/api.hpp>
#include <pcg/engine/core/node.hpp>

#include <vector>

using namespace pcg::engine::core;
using namespace pcg::engine::math;

namespace
{
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
    generation1D(&data, Axis::x, Direction::negative, addPoints);

    std::cout << "2D Generation" << std::endl;
    generation2D(&data, Plane::yz, true, addPoints);

    std::cout << "3D Generation" << std::endl;
    generation3D(&data, true, addPoints);

    std::cout << "Wave Function Collapse DFS" << std::endl;
    data.limit = 115;
    waveFunctionCollapse(&data, ExpansionMode::DFS, addWFCPoints);
    std::cout << "Wave Function Collapse BFS" << std::endl;
    waveFunctionCollapse(&data, ExpansionMode::BFS, addWFCPoints);

    return 0;
}
