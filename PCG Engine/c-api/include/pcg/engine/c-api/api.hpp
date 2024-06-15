#ifndef PCG_ENGINE_C_API_API_HPP
#define PCG_ENGINE_C_API_API_HPP

#include <pcg/engine/c-api/config.hpp>

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/maze/enums.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::c_api
{
    typedef void (*addPointCallback)(math::Vector3 vector);
    typedef void (*addWFCPointCallback)(math::Vector3 vector, int neighbors);
    typedef void (*addMazePointCallback)(int x, int y, int neighbors);
    typedef void (*setSeedCallback)(unsigned int seed);
    typedef int (*generateNumberCallback)(int minimum, int maximum);
    typedef void (*logMessage)(const char* message);

    PCG_ENGINE_C_API_API void setSeed(unsigned int seed);
    PCG_ENGINE_C_API_API void setRandomGenerator(setSeedCallback seed, generateNumberCallback generate);
    PCG_ENGINE_C_API_API void setLoggingFunction(logMessage logFunction);
    PCG_ENGINE_C_API_API void simpleGeneration(level_generation::GenerationData* data, math::axis::Flag axis, math::Direction direction, addPointCallback callback);
    PCG_ENGINE_C_API_API void multiDimensionGeneration(level_generation::GenerationData* data, math::axis::Flag axis, bool disableOverlap, addPointCallback callback);
    PCG_ENGINE_C_API_API void waveFunctionCollapseGeneration(level_generation::GenerationData* data, level_generation::ExpansionMode mode, addWFCPointCallback callback);
    PCG_ENGINE_C_API_API void generateMaze(int width, int height, maze::MazeAlgorithm algorithm, addMazePointCallback callback);
}

#endif // PCG_ENGINE_C_API_API_HPP
