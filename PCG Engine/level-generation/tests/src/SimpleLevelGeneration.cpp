#include <pcg/engine/level-generation/SimpleGeneration.hpp>

#include <gtest/gtest.h>

namespace pcg::engine::level_generation::tests
{
    struct SimpleLevelGenerationParam
    {
        SimpleLevelGenerationParam(math::Axis axis) : axis(axis)
        {
        }

        void setCallback()
        {
            switch (axis)
            {
            case math::Axis::positiveX:
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.x, points[index]);
                        index += 1;
                    };
                break;
            }
            case math::Axis::negativeX:
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.x, -points[index]);
                        index += 1;
                    };
                break;
            }
            case math::Axis::positiveY:
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.y, points[index]);
                        index += 1;
                    };
                break;
            }
            case math::Axis::negativeY:
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.y, -points[index]);
                        index += 1;
                    };
                break;
            }
            case math::Axis::positiveZ:
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.z, points[index]);
                        index += 1;
                    };
                break;
            }
            case math::Axis::negativeZ:
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.z, -points[index]);
                        index += 1;
                    };
                break;
            }
            default:
            {
                break;
            }
            }
        }

        math::Axis axis;
        std::function<void(math::Vector3)> callback = nullptr;

    private:
        std::vector<int> points{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int index = 0;
    };

    class SimpleLevelGenerationTest : public ::testing::TestWithParam<SimpleLevelGenerationParam>
    {
    public:
        struct PrintToStringParamName
        {
            template <class ParamType>
            std::string operator()(const testing::TestParamInfo<ParamType>& info) const
            {
                switch (static_cast<SimpleLevelGenerationParam>(info.param).axis)
                {
                case math::Axis::positiveX:
                {
                    return "PositiveX";
                }
                case math::Axis::negativeX:
                {
                    return "NegativeX";
                }
                case math::Axis::positiveY:
                {
                    return "PositiveY";
                }
                case math::Axis::negativeY:
                {
                    return "NegativeY";
                }
                case math::Axis::positiveZ:
                {
                    return "PositiveZ";
                }
                case math::Axis::negativeZ:
                {
                    return "NegativeZ";
                }
                default:
                    return "";
                }
            }
        };
    };

    TEST_P(SimpleLevelGenerationTest, SimpleLevelGeneration)
    {
        GenerationData data{ 10, 1, math::Vector3::zero };
        SimpleLevelGenerationParam levelGenerationParam = GetParam();
        levelGenerationParam.setCallback();

        simpleGeneration(data, levelGenerationParam.axis, levelGenerationParam.callback);
    }

    INSTANTIATE_TEST_CASE_P(
        SimpleLevelGenerationTests,
        SimpleLevelGenerationTest,
        ::testing::Values(
            SimpleLevelGenerationParam(math::Axis::positiveX),
            SimpleLevelGenerationParam(math::Axis::negativeX),
            SimpleLevelGenerationParam(math::Axis::positiveY),
            SimpleLevelGenerationParam(math::Axis::negativeY),
            SimpleLevelGenerationParam(math::Axis::positiveZ),
            SimpleLevelGenerationParam(math::Axis::negativeZ)
        ),
        SimpleLevelGenerationTest::PrintToStringParamName());
}
