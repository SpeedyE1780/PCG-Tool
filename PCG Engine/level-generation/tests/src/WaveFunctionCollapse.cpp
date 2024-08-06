#include <pcg/engine/level-generation/WaveFunctionCollapse.hpp>

#include <pcg/engine/math/random.hpp>

#include <gtest/gtest.h>

#include <functional>
#include <fstream>

namespace pcg::engine::level_generation::tests
{
    TEST(WaveFunctionCollapse, BFS)
    {
        math::Random::resetSeed();
        std::ofstream input("GoldenValues/WaveFunctionCollapse/BFS.txt");

        GenerationData data{ 200, 1, math::Vector3::zero };

        std::function<void(math::Vector3, utility::enums::Direction)> callback = [&input](math::Vector3 position, utility::enums::Direction direction)
            {
                input << position.x << " " << position.y << " " << position.z << " " << static_cast<int>(direction) << std::endl;
            };

        waveFunctionCollapse(data, ExpansionMode::BFS, math::Axis::xyz, callback);
    }

    TEST(WaveFunctionCollapse, DFS)
    {
        math::Random::resetSeed();
        std::ofstream input("GoldenValues/WaveFunctionCollapse/DFS.txt");

        GenerationData data{ 200, 1, math::Vector3::zero };

        std::function<void(math::Vector3, utility::enums::Direction)> callback = [&input](math::Vector3 position, utility::enums::Direction direction)
            {
                input << position.x << " " << position.y << " " << position.z << " " << static_cast<int>(direction) << std::endl;
            };

        waveFunctionCollapse(data, ExpansionMode::BFS, math::Axis::xyz, callback);
    }

    TEST(WaveFunctionCollapse, Grid2D)
    {
        math::Random::resetSeed();
        std::ofstream input("GoldenValues/WaveFunctionCollapse/Grid2D.txt");

        std::function<void(int, int, utility::enums::Direction)> callback = [&input](int x, int y, utility::enums::Direction direction)
            {
                input << x << " " << y << " " << static_cast<int>(direction) << std::endl;
            };

        waveFunctionCollapse(10, 10, math::Axis::xz, false, callback);
    }

    TEST(WaveFunctionCollapse, Grid3D)
    {
        math::Random::resetSeed();
        std::ofstream input("GoldenValues/WaveFunctionCollapse/Grid3D.txt");

        std::function<void(int, int, int, utility::enums::Direction)> callback = [&input](int x, int y, int z, utility::enums::Direction direction)
            {
                input << x << " " << y << " " << z << " " << static_cast<int>(direction) << std::endl;
            };

        waveFunctionCollapse(10, 10, 10, false, callback);
    }
}
