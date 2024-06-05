#include <pcg/engine/core/core.hpp>

namespace pcg::engine::core
{
    int add(int x, int y)
    {
        return x + y;
    }

    void simpleGeneration(GenerationData* data, addPointCallback callback)
    {
        Vector3 position = data->startPoint;

        for (int i = 0; i < data->limit; i++)
        {
            callback(position);
            position.z += data->size;
        }
    }
}
