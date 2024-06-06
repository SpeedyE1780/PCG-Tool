#include <iostream>>
#include <pcg/engine/core/core.hpp>

#include <vector>

using namespace pcg::engine::core;

std::vector<Vector3> points{};

void addPoints(Vector3 point)
{
    points.push_back(point);
}

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "Add 1 + 5 = " << add(1, 5) << std::endl;
    GenerationData data{ 10, 1, {0,0,0} };
    simpleGeneration(&data, Axis::x, addPoints);

    for (auto& p : points)
    {
        std::cout << "P:" << p.x << "," <<p.y << "," << p.z << std::endl;
    }

    return 0;
}
