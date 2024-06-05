#include <pcg/engine/core/core.hpp>

namespace pcg::engine::core
{
    int add(int x, int y)
    {
        return x + y;
    }

    void simpleGeneration(std::function<void(float, float, float)> callback)
    {
        float x = 0;
        float y = 0;
        float z = 0;

        for (int i = 0; i < 10; i++)
        {
            callback(x, y, z);
            z += 1;
        }
    }
}
