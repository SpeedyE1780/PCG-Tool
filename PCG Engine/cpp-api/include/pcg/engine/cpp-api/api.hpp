#ifndef PCG_ENGINE_CPP_API_API_HPP
#define PCG_ENGINE_CPP_API_API_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/cpp-api/config.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/Vector3.hpp>

#include <pcg/engine/utility/Enums.hpp>

#include <functional>

namespace pcg::engine::cpp_api
{
    /// @brief Indicates which algorithm to use when generating mazes
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

    /// @brief Set RNG's seed
    /// @param seed New RNG seed
    PCG_ENGINE_CPP_API_API void setSeed(unsigned int seed);
    /// @brief Set functions used to set seed and generate numbers
    /// @param seed Function that will set the RNG seed
    /// @param generate Function used to generate numbers
    PCG_ENGINE_CPP_API_API void setRandomGenerator(std::function<void(unsigned int)>&& seed, std::function<int(int, int)>&& generate);
    /// @brief Set function used to log messages from the engine
    /// @param logFunction Function that will log engine messages
    PCG_ENGINE_CPP_API_API void setLoggingFunction(std::function<void(const char*)>&& logFunction);
    /// @brief Generate a linear level on a single axis
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param axis Axis used during level generation (X, Y or Z)
    /// @param direction Direction followed on axis (Either positive or negative)
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void simpleGeneration(level_generation::GenerationData* data, math::Axis axis, math::Direction direction, std::function<void(math::Vector3)>&& callback);
    /// @brief Generate a level on multiple axes
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param axes Axes flag indicating which axes are being used
    /// @param disableOverlap If true nodes cannot be generated on top of one another
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void multiDimensionGeneration(level_generation::GenerationData* data, math::Axis axes, bool disableOverlap, std::function<void(math::Vector3)>&& callback);
    /// @brief Generate a level using the Wave Function Collapse Algorithm
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param mode If Breadth-First Search (BFS) or Depth-First Search (DFS) expansion should be used
    /// @param axes Axes flag indicating which axes are being used
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void waveFunctionCollapseGeneration(level_generation::GenerationData* data, level_generation::ExpansionMode mode, math::Axis axes, std::function<void(math::Vector3, utility::enums::Direction)>&& callback);
    /// @brief Generate a maze using the passed in algorithm
    /// @param width Width of grid
    /// @param height Height of grid
    /// @param invokeAferGeneration If true callback will only be called after all nodes are generated
    /// @param algorithm Algorithm that will be used to generate maze
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void generateMaze(int width, int height, bool invokeAferGeneration, MazeAlgorithm algorithm, std::function<void(int x, int y, utility::enums::Direction neighbors)>&& callback);
    /// @brief Generate a combination given a number of elements
    /// @param elementCount Number of element that are available in set
    /// @param callback Callback to add element to generated set
    PCG_ENGINE_CPP_API_API void generateCombination(int elementCount, std::function<void(int, bool)>&& callback);
    /// @brief Generate a combination with at least minimumElementCount elements
    /// @param elementCount Number of element that are available in set
    /// @param minimumElementCount Minimum number of elements in set
    /// @param callback Callback to add element to generated set
    PCG_ENGINE_CPP_API_API void generateCombination(int elementCount, int minimumElementCount, std::function<void(int, bool)>&& callback);
    /// @brief Generate a combination with the given elements active
    /// @param elementCount Number of element that are available in set
    /// @param activeElementsIndex Array of elements that must be included
    /// @param callback Callback to add element to generated set
    PCG_ENGINE_CPP_API_API void generateCombination(int elementCount, const std::vector<int>& activeElementsIndex, std::function<void(int, bool)>&& callback);
}

#endif // PCG_ENGINE_CPP_API_API_HPP
