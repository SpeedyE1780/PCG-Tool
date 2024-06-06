#include <iostream>>
#include <pcg/engine/core/generators.hpp>

#include <vector>

using namespace pcg::engine::core;
using namespace pcg::engine::math;

std::vector<Vector3> points{};

void addPoints(Vector3 point)
{
    points.push_back(point);
}

int main()
{
    std::cout << "Simple Generation" << std::endl;
    GenerationData data{ 10, 1, { 0, 0, 0 } };
    simpleGeneration(&data, Axis::x, Direction::negative, addPoints);

    for (auto& p : points)
    {
        std::cout << "P:" << p.x << "," << p.y << "," << p.z << std::endl;
    }

    points.clear();
    std::cout << "2D Generation" << std::endl;
    generation2D(&data, Plane::yz, true, addPoints);

    for (auto& p : points)
    {
        std::cout << "P:" << p.x << "," << p.y << "," << p.z << std::endl;
    }

    points.clear();
    std::cout << "3D Generation" << std::endl;
    generation3D(&data, true, addPoints);

    for (auto& p : points)
    {
        std::cout << "P:" << p.x << "," << p.y << "," << p.z << std::endl;
    }

    return 0;
}
