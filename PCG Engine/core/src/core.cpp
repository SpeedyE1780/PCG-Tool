#include <pcg/engine/core/core.hpp>

namespace pcg::engine::core
{
    int add(int x, int y)
    {
        return x + y;
    }

    void simpleGeneration(GenerationData* data, addPointCallback callback)
    {
        float x = data->startPoint.x;
        float y = data->startPoint.y;
        float z = data->startPoint.z;

        for (int i = 0; i < data->limit; i++)
        {
            callback(x, y, z);
            z += data->size;
        }
    }
}
