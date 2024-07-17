#include <pcg/engine/level-generation/MultiDimensionalGeneration.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <unordered_set>

namespace pcg::engine::level_generation::tests
{
    namespace
    {
        void px(const math::Vector3& position)
        {
            ASSERT_TRUE(position.x >= 0);
        }

        void nx(const math::Vector3& position)
        {
            ASSERT_TRUE(position.x <= 0);
        }

        void py(const math::Vector3& position)
        {
            ASSERT_TRUE(position.y >= 0);
        }

        void ny(const math::Vector3& position)
        {
            ASSERT_TRUE(position.y <= 0);
        }

        void pz(const math::Vector3& position)
        {
            ASSERT_TRUE(position.z >= 0);
        }

        void nz(const math::Vector3& position)
        {
            ASSERT_TRUE(position.z <= 0);
        }
    }

    struct MultiDimensionalGenerationParam
    {
        void positionCheck(const math::Vector3& position)
        {
            for (const auto& positionCheck : positionCheckers)
            {
                positionCheck(position);
            }
        }

        void fillPositionCheckers()
        {
            if (utility::enums::hasFlag(axis, math::Axis::positiveX) && !utility::enums::hasFlag(axis, math::Axis::negativeX))
            {
                positionCheckers.push_back(px);
            }

            if (utility::enums::hasFlag(axis, math::Axis::negativeX) && !utility::enums::hasFlag(axis, math::Axis::positiveX))
            {
                positionCheckers.push_back(nx);
            }

            if (utility::enums::hasFlag(axis, math::Axis::positiveY) && !utility::enums::hasFlag(axis, math::Axis::negativeY))
            {
                positionCheckers.push_back(py);
            }

            if (utility::enums::hasFlag(axis, math::Axis::negativeY) && !utility::enums::hasFlag(axis, math::Axis::positiveY))
            {
                positionCheckers.push_back(ny);
            }

            if (utility::enums::hasFlag(axis, math::Axis::positiveZ) && !utility::enums::hasFlag(axis, math::Axis::negativeZ))
            {
                positionCheckers.push_back(pz);
            }

            if (utility::enums::hasFlag(axis, math::Axis::negativeZ) && !utility::enums::hasFlag(axis, math::Axis::positiveZ))
            {
                positionCheckers.push_back(nz);
            }
        }

        math::Axis axis;
        std::string fileName;
        std::vector<std::function<void(math::Vector3)>> positionCheckers{};
    };

    class MultiDimensionalGenerationTest : public ::testing::TestWithParam<MultiDimensionalGenerationParam>
    {
    public:
        struct PrintToStringParamName
        {
            template <class ParamType>
            std::string operator()(const testing::TestParamInfo<ParamType>& info) const
            {
                return static_cast<MultiDimensionalGenerationParam>(info.param).fileName;
            }
        };
    };

    TEST_P(MultiDimensionalGenerationTest, MultiDimensionalGenerationNoOverlap)
    {
        GenerationData data{ 150, 1, math::Vector3::zero };
        MultiDimensionalGenerationParam levelGenerationParam = GetParam();
        levelGenerationParam.fillPositionCheckers();

        std::ostringstream oss{};
        oss << "GoldenValues/NoOverlap/" << levelGenerationParam.fileName << ".txt";

        std::ifstream input(oss.str());
        std::unordered_set<math::Vector3> positions{};

        std::function<void(math::Vector3)> callback = [&levelGenerationParam, &input, &positions](math::Vector3 position)
            {
                ASSERT_TRUE(positions.find(position) == positions.end());
                positions.insert(position);

                int x = 0;
                int y = 0;
                int z = 0;

                input >> x >> y >> z;
                levelGenerationParam.positionCheck(position);

                EXPECT_EQ(x, position.x);
                EXPECT_EQ(y, position.y);
                EXPECT_EQ(z, position.z);
            };

        multiDimensionalGeneration(data, levelGenerationParam.axis, true, callback);
        input.close();
    }

    TEST_P(MultiDimensionalGenerationTest, MultiDimensionalGenerationOverlap)
    {
        GenerationData data{ 150, 1, math::Vector3::zero };
        MultiDimensionalGenerationParam levelGenerationParam = GetParam();
        levelGenerationParam.fillPositionCheckers();

        std::ostringstream oss{};
        oss << "GoldenValues/Overlap/" << levelGenerationParam.fileName << ".txt";

        std::ifstream input(oss.str());

        std::function<void(math::Vector3)> callback = [&levelGenerationParam, &input](math::Vector3 position)
            {
                int x = 0;
                int y = 0;
                int z = 0;

                input >> x >> y >> z;
                levelGenerationParam.positionCheck(position);

                EXPECT_EQ(x, position.x);
                EXPECT_EQ(y, position.y);
                EXPECT_EQ(z, position.z);
            };

        multiDimensionalGeneration(data, levelGenerationParam.axis, false, callback);
        input.close();
    }

    INSTANTIATE_TEST_CASE_P(
        MultiDimensionalGenerationTests,
        MultiDimensionalGenerationTest,
        ::testing::Values(
            MultiDimensionalGenerationParam{ math::Axis::x, "X" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::positiveY, "PxPy" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::positiveY, "NxPy" },
            MultiDimensionalGenerationParam{ math::Axis::x | math::Axis::positiveY, "XPy" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::negativeY, "PxNy" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::negativeY, "NxNy" },
            MultiDimensionalGenerationParam{ math::Axis::x | math::Axis::negativeY, "XNy" },
            MultiDimensionalGenerationParam{ math::Axis::y, "Y" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::y, "PxY" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::y, "NxY" },
            MultiDimensionalGenerationParam{ math::Axis::xy, "XY" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::positiveZ, "PxPz" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::positiveZ, "NxPz" },
            MultiDimensionalGenerationParam{ math::Axis::x | math::Axis::positiveZ, "XPz" },
            MultiDimensionalGenerationParam{ math::Axis::positiveY | math::Axis::positiveZ, "PyPz" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::positiveY | math::Axis::positiveZ, "PxPyPz" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::positiveY | math::Axis::positiveZ, "NxPyPz" },
            MultiDimensionalGenerationParam{ math::Axis::x | math::Axis::positiveY | math::Axis::positiveZ, "XPyPZ" },
            MultiDimensionalGenerationParam{ math::Axis::negativeY | math::Axis::positiveZ, "NyPz" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::negativeY | math::Axis::positiveZ, "PxNyPz" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::negativeY | math::Axis::positiveZ, "NxNyPz" },
            MultiDimensionalGenerationParam{ math::Axis::x | math::Axis::negativeY | math::Axis::positiveZ, "XNyPz" },
            MultiDimensionalGenerationParam{ math::Axis::y | math::Axis::positiveZ, "YPz" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::y | math::Axis::positiveZ, "PxYPz" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::y | math::Axis::positiveZ, "NxYPz" },
            MultiDimensionalGenerationParam{ math::Axis::xy | math::Axis::positiveZ, "XYPz" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::negativeZ, "PxNz" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::negativeZ, "NxNz" },
            MultiDimensionalGenerationParam{ math::Axis::x | math::Axis::negativeZ, "XNz" },
            MultiDimensionalGenerationParam{ math::Axis::positiveY | math::Axis::negativeZ, "PyNz" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::positiveY | math::Axis::negativeZ, "PxPyNz" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::positiveY | math::Axis::negativeZ, "NxPyNz" },
            MultiDimensionalGenerationParam{ math::Axis::x | math::Axis::positiveY | math::Axis::negativeZ, "XPyNz" },
            MultiDimensionalGenerationParam{ math::Axis::negativeY | math::Axis::negativeZ, "NyNz" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::negativeY | math::Axis::negativeZ, "PxNyNz" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::negativeY | math::Axis::negativeZ, "NxNyNz" },
            MultiDimensionalGenerationParam{ math::Axis::x | math::Axis::negativeY | math::Axis::negativeZ, "XNyNz" },
            MultiDimensionalGenerationParam{ math::Axis::y | math::Axis::negativeZ, "YNz" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::y | math::Axis::negativeZ, "PxYNz" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::y | math::Axis::negativeZ, "NxYNz" },
            MultiDimensionalGenerationParam{ math::Axis::xy | math::Axis::negativeZ, "XYNz" },
            MultiDimensionalGenerationParam{ math::Axis::z , "Z" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::z , "PxZ" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::z , "NxZ" },
            MultiDimensionalGenerationParam{ math::Axis::xz , "XZ" },
            MultiDimensionalGenerationParam{ math::Axis::positiveY | math::Axis::z, "PyZ" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::positiveY | math::Axis::z, "PxPyZ" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::positiveY | math::Axis::z, "NxPyZ" },
            MultiDimensionalGenerationParam{ math::Axis::xz | math::Axis::positiveY, "XPyZ" },
            MultiDimensionalGenerationParam{ math::Axis::negativeY | math::Axis::positiveY, "NyZ" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::negativeY | math::Axis::positiveY, "PxNyZ" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::negativeY | math::Axis::positiveY, "NxNyZ" },
            MultiDimensionalGenerationParam{ math::Axis::xz | math::Axis::negativeY, "XNyZ" },
            MultiDimensionalGenerationParam{ math::Axis::yz, "YZ" },
            MultiDimensionalGenerationParam{ math::Axis::positiveX | math::Axis::yz, "PxYZ" },
            MultiDimensionalGenerationParam{ math::Axis::negativeX | math::Axis::yz, "NxYZ" },
            MultiDimensionalGenerationParam{ math::Axis::xyz, "XYZ" }
        ),
        MultiDimensionalGenerationTest::PrintToStringParamName());
}
