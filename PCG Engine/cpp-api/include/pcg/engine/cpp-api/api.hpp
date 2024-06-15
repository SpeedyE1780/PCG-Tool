#ifndef PCG_ENGINE_CPP_API_API_HPP
#define PCG_ENGINE_CPP_API_API_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/cpp-api/config.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze/Enums.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <functional>

namespace pcg::engine::cpp_api
{
    PCG_ENGINE_CPP_API_API void setSeed(unsigned int seed);
    PCG_ENGINE_CPP_API_API void setRandomGenerator(std::function<void(unsigned int)>&& seed, std::function<int(int, int)>&& generate);
    PCG_ENGINE_CPP_API_API void setLoggingFunction(std::function<void(const char*)>&& logFunction);
    PCG_ENGINE_CPP_API_API void simpleGeneration(level_generation::GenerationData* data, math::axis::Flag axis, math::Direction direction, std::function<void(math::Vector3)>&& callback);
    PCG_ENGINE_CPP_API_API void multiDimensionGeneration(level_generation::GenerationData* data, math::axis::Flag axis, bool disableOverlap, std::function<void(math::Vector3)>&& callback);
    PCG_ENGINE_CPP_API_API void waveFunctionCollapseGeneration(level_generation::GenerationData* data, level_generation::ExpansionMode mode, std::function<void(math::Vector3, int)>&& callback);
    PCG_ENGINE_CPP_API_API void generateMaze(int width, int height, maze::MazeAlgorithm algorithm, std::function<void(int x, int y, int neighbors)>&& callback);
}

#endif // PCG_ENGINE_CPP_API_API_HPP
