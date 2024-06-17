#ifndef PCG_ENGINE_CPP_API_API_HPP
#define PCG_ENGINE_CPP_API_API_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/cpp-api/config.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>
#include <pcg/engine/utility/Enums.hpp>

#include <functional>

namespace pcg::engine::cpp_api
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

    PCG_ENGINE_CPP_API_API void setSeed(unsigned int seed);
    PCG_ENGINE_CPP_API_API void setRandomGenerator(std::function<void(unsigned int)>&& seed, std::function<int(int, int)>&& generate);
    PCG_ENGINE_CPP_API_API void setLoggingFunction(std::function<void(const char*)>&& logFunction);
    PCG_ENGINE_CPP_API_API void simpleGeneration(level_generation::GenerationData* data, math::Axis axis, math::Direction direction, std::function<void(math::Vector3)>&& callback);
    PCG_ENGINE_CPP_API_API void multiDimensionGeneration(level_generation::GenerationData* data, math::Axis axis, bool disableOverlap, std::function<void(math::Vector3)>&& callback);
    PCG_ENGINE_CPP_API_API void waveFunctionCollapseGeneration(level_generation::GenerationData* data, level_generation::ExpansionMode mode, math::Axis axis, std::function<void(math::Vector3, utility::enums::Direction)>&& callback);
    PCG_ENGINE_CPP_API_API void generateMaze(int width, int height, bool invokeAferGeneration, MazeAlgorithm algorithm, std::function<void(int x, int y, utility::enums::Direction neighbors)>&& callback);
    PCG_ENGINE_CPP_API_API void generateCombination(int elementCount, std::function<void(int, bool)>&& callback);
    PCG_ENGINE_CPP_API_API void generateCombination(int elementCount, int minimumElementCount, std::function<void(int, bool)>&& callback);
    PCG_ENGINE_CPP_API_API void generateCombination(int elementCount, const std::vector<int>& activeElementsIndex, std::function<void(int, bool)>&& callback);
}

#endif // PCG_ENGINE_CPP_API_API_HPP
