#include <iostream>>
#include <pcg/engine/core/core.hpp>

#include <vector>

std::vector<float> points{};

void addPoints(float x, float y, float z)
{
    points.push_back(x);
    points.push_back(y);
    points.push_back(z);
}

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "Add 1 + 5 = " << pcg::engine::core::add(1, 5) << std::endl;
    pcg::engine::core::simpleGeneration(addPoints);

    for (auto& p : points)
    {
        std::cout << "P:" << p << std::endl;
    }

    return 0;
}
