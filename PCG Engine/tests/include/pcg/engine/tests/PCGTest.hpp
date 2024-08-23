#ifndef PCG_ENGINE_TESTS_PCG_TEST_HPP
#define PCG_ENGINE_TESTS_PCG_TEST_HPP

#include <gtest/gtest.h>

namespace pcg::engine::tests
{
    class PCGTest : public ::testing::Test
    {
    public:
        ~PCGTest() = default;

    protected:
        virtual void SetUp() override;
    };
}

#endif // PCG_ENGINE_TESTS_PCG_TEST_HPP
