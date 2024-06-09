#include <iostream>>
#include <pcg/engine/core/generators.hpp>

#include <vector>

using namespace pcg::engine::core;
using namespace pcg::engine::math;

namespace
{
    void addPoints(Vector3 point)
    {
        std::cout << "Point:" << point.x << "," << point.y << "," << point.z << std::endl;
    }

    void logMessage(const std::string& message)
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
    generation2D(&data, Plane::yz, true, addPoints);

    std::cout << "3D Generation" << std::endl;
    generation3D(&data, true, addPoints);

    return 0;
}
