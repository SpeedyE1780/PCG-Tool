#ifndef PCG_ENGINE_CORE_API_HPP
#define PCG_ENGINE_CORE_API_HPP

#include <pcg/engine/core/GenerationData.hpp>
#include <pcg/engine/core/Maze.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>
#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::core
{
    enum class MazeAlgorithm
    {
        aldousBroder = 0,
        wilson = 1,
        binaryTreeNE = 2,
        binaryTreeNW = 3,
        binaryTreeSE = 4,
        binaryTreeSW = 5,
        sidewinder = 6
    };

    void setSeed(unsigned int seed);
    void setRandomGenerator(math::setSeed seed, math::generateNumber generate);
    void setLoggingFunction(utility::logMessage logFunction);
    void generation1D(GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback);
    void generation2D(GenerationData* data, math::Plane plane, bool disableOverlap, addPointCallback callback);
    void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback);
    void waveFunctionCollapseGeneration(GenerationData* data, ExpansionMode mode, addWFCPointCallback callback);
    void generateMaze(int width, int height, MazeAlgorithm algorithm, addMazePointCallback callback);
}

#endif // PCG_ENGINE_CORE_API_HPP
