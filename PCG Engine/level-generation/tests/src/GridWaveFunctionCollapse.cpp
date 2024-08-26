#include <pcg/engine/level-generation/GridWaveFunctionCollapse.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/tests/PCGTest.hpp>

#include <gtest/gtest.h>

#include <fstream>

using PCGTest = pcg::engine::tests::PCGTest;

namespace pcg::engine::level_generation::tests
{
    namespace
    {
        struct Grid2DParam
        {
            math::Plane plane;
            std::string fileName;
        };

        class Grid2DWaveFunctionCollapse : public ::testing::TestWithParam<Grid2DParam>
        {
        public:
            struct PrintToStringParamName
            {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& info) const
                {
                    return static_cast<Grid2DParam>(info.param).fileName;
                }
            };
        };

        class Grid3DWaveFunctionCollapse : public PCGTest
        {
        };
    }

    TEST_P(Grid2DWaveFunctionCollapse, Grid2D)
    {
        math::Random::resetSeed();
        auto [plane, fileName] = GetParam();
        std::ostringstream oss{};
        oss << "GoldenValues/WaveFunctionCollapse/" << fileName << ".txt";
        std::ifstream input(oss.str());

        waveFunctionCollapse(10, 10, plane, false, [&input](int x, int y, utility::enums::Direction adjacentNodes)
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

    INSTANTIATE_TEST_CASE_P(Grid2DWaveFunctionCollapseTests,
        Grid2DWaveFunctionCollapse,
        ::testing::Values(
            Grid2DParam{ math::Plane::xy, "Grid2DXY" },
            Grid2DParam{ math::Plane::xz, "Grid2DXZ" },
            Grid2DParam{ math::Plane::yz, "Grid2DYZ" }
        ),
        Grid2DWaveFunctionCollapse::PrintToStringParamName());

    TEST_F(Grid3DWaveFunctionCollapse, Grid3D)
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
