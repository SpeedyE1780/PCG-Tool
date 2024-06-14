#include <pcg/engine/cpp-api/api.hpp>

namespace pcg::engine::cpp_api
{
    void setSeed(unsigned int seed)
    {
        core::setSeed(seed);
    }

    void setRandomGenerator(math::setSeed seed, math::generateNumber generate)
    {
        return core::setRandomGenerator(seed, generate);
    }

    void setLoggingFunction(utility::logMessage logFunction)
    {
        core::setLoggingFunction(logFunction);
    }

    void generation1D(core::GenerationData* data, math::Axis axis, math::Direction direction, core::addPointCallback callback)
    {
        core::generation1D(data, axis, direction, callback);
    }

    void generation2D(core::GenerationData* data, math::Plane plane, bool disableOverlap, core::addPointCallback callback)
    {
        core::generation2D(data, plane, disableOverlap, callback);
    }

    void generation3D(core::GenerationData* data, bool disableOverlap, core::addPointCallback callback)
    {
        core::generation3D(data, disableOverlap, callback);
    }

    void waveFunctionCollapseGeneration(core::GenerationData* data, core::ExpansionMode mode, core::addWFCPointCallback callback)
    {
        core::waveFunctionCollapseGeneration(data, mode, callback);
    }

    void generateMaze(int width, int height, core::MazeAlgorithm algorithm, core::addMazePointCallback callback)
    {
        core::generateMaze(width, height, algorithm, callback);
    }
}

