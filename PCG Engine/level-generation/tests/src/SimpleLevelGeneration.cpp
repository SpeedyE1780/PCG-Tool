#include <pcg/engine/level-generation/SimpleGeneration.hpp>

#include <gtest/gtest.h>

namespace pcg::engine::level_generation::tests
{
    struct SimpleLevelGenerationParam
    {
        SimpleLevelGenerationParam(math::Vector3 offset) : offset(offset)
        {
        }

        void setCallback()
        {
            if (offset == math::Vector3::right)
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.x, points[index]);
                        index += 1;
                    };
            }
            else if (offset == math::Vector3::left)
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.x, -points[index]);
                        index += 1;
                    };
            }
            else if (offset == math::Vector3::up)
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.y, points[index]);
                        index += 1;
                    };
            }
            else if (offset == math::Vector3::down)
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.y, -points[index]);
                        index += 1;
                    };
            }
            else if (offset == math::Vector3::forward)
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.z, points[index]);
                        index += 1;
                    };
            }
            else if (offset == math::Vector3::backward)
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.z, -points[index]);
                        index += 1;
                    };
            }
            else if (offset == math::Vector3::zero)
            {
                callback = [this](math::Vector3 position)
                    {
                        EXPECT_EQ(position.x, 0);
                        EXPECT_EQ(position.y, 0);
                        EXPECT_EQ(position.z, 0);
                    };
            }
        }

        math::Vector3 offset;
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
                const auto& offset = static_cast<SimpleLevelGenerationParam>(info.param).offset;

                if (offset == math::Vector3::right)
                {
                    return "PositiveX";
                }
                else if (offset == math::Vector3::left)
                {
                    return "NegativeX";
                }
                else if (offset == math::Vector3::up)
                {
                    return "PositiveY";
                }
                else if (offset == math::Vector3::down)
                {
                    return "NegativeY";
                }
                else if (offset == math::Vector3::forward)
                {
                    return "PositiveZ";
                }
                else if (offset == math::Vector3::backward)
                {
                    return "NegativeZ";
                }
                else if (offset == math::Vector3::zero)
                {
                    return "Zero";
                }
            };
        };
    };

    TEST_P(SimpleLevelGenerationTest, SimpleLevelGeneration)
    {
        GenerationData data{ 10, 1, math::Vector3::zero };
        SimpleLevelGenerationParam levelGenerationParam = GetParam();
        levelGenerationParam.setCallback();

        simpleGeneration(data, levelGenerationParam.offset, levelGenerationParam.callback);
    }

    INSTANTIATE_TEST_CASE_P(
        SimpleLevelGenerationTests,
        SimpleLevelGenerationTest,
        ::testing::Values(
            SimpleLevelGenerationParam(math::Vector3::right),
            SimpleLevelGenerationParam(math::Vector3::left),
            SimpleLevelGenerationParam(math::Vector3::up),
            SimpleLevelGenerationParam(math::Vector3::down),
            SimpleLevelGenerationParam(math::Vector3::forward),
            SimpleLevelGenerationParam(math::Vector3::backward),
            SimpleLevelGenerationParam(math::Vector3::zero)
        ),
        SimpleLevelGenerationTest::PrintToStringParamName());
}
