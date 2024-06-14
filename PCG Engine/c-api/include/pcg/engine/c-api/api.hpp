#ifndef PCG_ENGINE_C_API_API_HPP
#define PCG_ENGINE_C_API_API_HPP

#include <pcg/engine/c-api/config.hpp>

#include <pcg/engine/core/GenerationData.hpp>

#include <pcg/engine/maze/enums.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::c_api
{
    typedef void (*addMazePointCallback)(int x, int y, int neighbors);

    PCG_ENGINE_C_API_API void setSeed(unsigned int seed);
    PCG_ENGINE_C_API_API void setRandomGenerator(math::setSeed seed, math::generateNumber generate);
    PCG_ENGINE_C_API_API void setLoggingFunction(utility::logMessage logFunction);
    PCG_ENGINE_C_API_API void generation1D(core::GenerationData* data, math::Axis axis, math::Direction direction, core::addPointCallback callback);
    PCG_ENGINE_C_API_API void generation2D(core::GenerationData* data, math::Plane plane, bool disableOverlap, core::addPointCallback callback);
    PCG_ENGINE_C_API_API void generation3D(core::GenerationData* data, bool disableOverlap, core::addPointCallback callback);
    PCG_ENGINE_C_API_API void waveFunctionCollapseGeneration(core::GenerationData* data, core::ExpansionMode mode, core::addWFCPointCallback callback);
    PCG_ENGINE_C_API_API void generateMaze(int width, int height, maze::MazeAlgorithm algorithm, addMazePointCallback callback);
}

#endif // PCG_ENGINE_C_API_API_HPP
