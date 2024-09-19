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

            GenerationData data{ 200, 1, math::Vector3::zero };
        };

        void checkWFCData(std::ifstream& input, const math::Vector3& position, utility::enums::Direction adjacentNodes)
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
        }

        void checkWFCData(std::ifstream& input, const math::Vector4& position, utility::enums::Direction adjacentNodes)
        {
            int x = 0;
            int y = 0;
            int z = 0;
            int w = 0;
            int adjacent = 0;

            input >> x >> y >> z >> w >> adjacent;
            EXPECT_EQ(x, position.x);
            EXPECT_EQ(y, position.y);
            EXPECT_EQ(z, position.z);
            EXPECT_EQ(w, position.w);
            EXPECT_EQ(static_cast<utility::enums::Direction>(adjacent), adjacentNodes);
        }
    }

    TEST_F(WaveFunctionCollapse, BFS)
    {
        std::ifstream input("GoldenValues/WaveFunctionCollapse/BFS.txt");

        waveFunctionCollapse(data, ExpansionMode::BFS, math::Axis::xyz, [&input](math::Vector3 position, utility::enums::Direction adjacentNodes)
            {
                checkWFCData(input, position, adjacentNodes);
            });
    }

    TEST_F(WaveFunctionCollapse, DFS)
    {
        std::ifstream input("GoldenValues/WaveFunctionCollapse/DFS.txt");

        waveFunctionCollapse(data, ExpansionMode::DFS, math::Axis::xyz, [&input](math::Vector3 position, utility::enums::Direction adjacentNodes)
            {
                checkWFCData(input, position, adjacentNodes);
            });
    }

    TEST_F(WaveFunctionCollapse, BFS4D)
    {
        std::ifstream input("GoldenValues/WaveFunctionCollapse/4DBFS.txt");

        waveFunctionCollapse4D(data, ExpansionMode::BFS, math::Axis::xyz, [&input](math::Vector4 position, utility::enums::Direction adjacentNodes)
            {
                checkWFCData(input, position, adjacentNodes);
            });
    }

    TEST_F(WaveFunctionCollapse, DFS4D)
    {
        std::ifstream input("GoldenValues/WaveFunctionCollapse/4DDFS.txt");

        waveFunctionCollapse4D(data, ExpansionMode::DFS, math::Axis::xyz, [&input](math::Vector4 position, utility::enums::Direction adjacentNodes)
            {
                checkWFCData(input, position, adjacentNodes);
            });
    }
}
