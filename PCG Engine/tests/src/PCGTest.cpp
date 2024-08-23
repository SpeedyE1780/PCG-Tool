#include <pcg/engine/math/random.hpp>

#include <pcg/engine/tests/PCGTest.hpp>

namespace pcg::engine::tests
{
    void PCGTest::SetUp()
    {
        math::Random::resetSeed();
    }
}
