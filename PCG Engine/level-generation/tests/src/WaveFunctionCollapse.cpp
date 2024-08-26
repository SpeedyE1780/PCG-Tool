#include <pcg/engine/level-generation/GridWaveFunctionCollapse.hpp>
#include <pcg/engine/level-generation/WaveFunctionCollapse.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/tests/PCGTest.hpp>

#include <gtest/gtest.h>

#include <functional>
#include <fstream>

using PCGTest = pcg::engine::tests::PCGTest;

namespace pcg::engine::level_generation::tests
{
    namespace
    {
        class WaveFunctionCollapse : public PCGTest
        {
        protected:
            virtual void SetUp() override
            {
                PCGTest::SetUp();
            }

            GenerationData data{ 200, 1, math::Vector3::zero };
        };
    }

    TEST_F(WaveFunctionCollapse, BFS)
    {
        std::ifstream input("GoldenValues/WaveFunctionCollapse/BFS.txt");

        waveFunctionCollapse(data, ExpansionMode::BFS, math::Axis::xyz, [&input](math::Vector3 position, utility::enums::Direction adjacentNodes)
            {
                int x = 0;
                int y = 0;
                int z = 0;
                int adjacent = 0;

                input >> x >> y >> z >> adjacent;
                EXPECT_EQ(x, position.x);
                EXPECT_EQ(y, position.y);
                EXPECT_EQ(z, position.z);
                EXPECT_EQ(static_cast<utility::enums::Direction>(adjacent), adjacentNodes);
            });
    }

    TEST_F(WaveFunctionCollapse, DFS)
    {
        std::ifstream input("GoldenValues/WaveFunctionCollapse/DFS.txt");

        waveFunctionCollapse(data, ExpansionMode::DFS, math::Axis::xyz, [&input](math::Vector3 position, utility::enums::Direction adjacentNodes)
            {
                int x = 0;
                int y = 0;
                int z = 0;
                int adjacent = 0;

                input >> x >> y >> z >> adjacent;
                EXPECT_EQ(x, position.x);
                EXPECT_EQ(y, position.y);
                EXPECT_EQ(z, position.z);
                EXPECT_EQ(static_cast<utility::enums::Direction>(adjacent), adjacentNodes);
            });
    }

    TEST_F(WaveFunctionCollapse, Grid2D)
    {
        std::ifstream input("GoldenValues/WaveFunctionCollapse/Grid2D.txt");

        waveFunctionCollapse(10, 10, math::Axis::xz, false, [&input](int x, int y, utility::enums::Direction adjacentNodes)
            {
                int expectedX = 0;
                int expectedY = 0;
                int adjacent = 0;

                input >> expectedX >> expectedY >> adjacent;
                EXPECT_EQ(expectedX, x);
                EXPECT_EQ(expectedY, y);
                EXPECT_EQ(static_cast<utility::enums::Direction>(adjacent), adjacentNodes);
            });
    }

    TEST_F(WaveFunctionCollapse, Grid3D)
    {
        std::ifstream input("GoldenValues/WaveFunctionCollapse/Grid3D.txt");

        waveFunctionCollapse(10, 10, 10, false, [&input](int x, int y, int z, utility::enums::Direction adjacentNodes)
            {
                int expectedX = 0;
                int expectedY = 0;
                int expectedZ = 0;
                int adjacent = 0;

                input >> expectedX >> expectedY >> expectedZ >> adjacent;
                EXPECT_EQ(expectedX, x);
                EXPECT_EQ(expectedY, y);
                EXPECT_EQ(expectedZ, z);
                EXPECT_EQ(static_cast<utility::enums::Direction>(adjacent), adjacentNodes);
            });
    }
}
