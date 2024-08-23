#include <pcg/engine/tests/PCGTest.hpp>
#include <pcg/engine/math/random.hpp>

namespace pcg::engine::tests
{
    void PCGTest::SetUp()
    {
        math::Random::resetSeed();
    }
}

