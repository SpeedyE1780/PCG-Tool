#ifndef PCG_ENGINE_CPP_API_API_HPP
#define PCG_ENGINE_CPP_API_API_HPP

#include <pcg/engine/combination-generation/SequenceGenerator.hpp>

#include <pcg/engine/cpp-api/config.hpp>

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/Vector3.hpp>

#include <pcg/engine/maze-generation/Common.hpp>

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
        sidewinder = 6,
        eller = 7,
        huntAndKill = 8,
        recursiveBacktracker = 9,
        recursiveDivision = 10,
        kruskal = 11,
        prim = 12,
        growingTreeOldest = 13,
        growingTreeMiddle = 14,
        growingTreeNewest = 15,
        growingTreeRandom = 16,
        blobbyDivisionCorridors = 17,
        blobbyDivisionSmall = 18,
        blobbyDivisionMedium = 19,
        blobbyDivisionLarge = 20,
        blobbyDivisionHuge = 21,
    };

    /// @brief Set RNG's seed
    /// @param seed New RNG seed
    PCG_ENGINE_CPP_API_API void setSeed(unsigned int seed);
    /// @brief Reset RNG seed
    PCG_ENGINE_CPP_API_API void resetSeed();
    /// @brief Set functions used to set seed and generate numbers
    /// @param seed Function that will set the RNG seed
    /// @param generate Function used to generate numbers
    PCG_ENGINE_CPP_API_API void setRandomGenerator(std::function<void(unsigned int)>&& seed, std::function<int(int, int)>&& generate);
    /// @brief Set function used to log messages from the engine
    /// @param logFunction Function that will log engine messages
    PCG_ENGINE_CPP_API_API void setLoggingFunction(std::function<void(const char*)>&& logFunction);
    /// @brief Generate a linear level on a single axis
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param offset Offset between nodes
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void simpleGeneration(const level_generation::GenerationData& data, const math::Vector3& offset, std::function<void(math::Vector3)>&& callback);
    /// @brief Generate a level on multiple axes
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param axes Axes flag indicating which axes are being used
    /// @param disableOverlap If true nodes cannot be generated on top of one another
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void multiDimensionGeneration(const level_generation::GenerationData& data, math::Axis axes, bool disableOverlap, std::function<void(math::Vector3)>&& callback);
    /// @brief Generate a level using the Wave Function Collapse Algorithm
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param mode If Breadth-First Search (BFS) or Depth-First Search (DFS) expansion should be used
    /// @param axes Axes flag indicating which axes are being used
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void waveFunctionCollapseGeneration(const level_generation::GenerationData& data, level_generation::ExpansionMode mode, math::Axis axes, std::function<void(math::Vector3, utility::enums::Direction)>&& callback);
    /// @brief Generate a grid using the Wave Function Collapse Algorithm
    /// @param width Grid width
    /// @param height Grid height
    /// @param axes Axes flag indicating which axes are being used
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void waveFunctionCollapseGeneration(int width, int height, math::Axis axes, bool invokeAfterGeneration, std::function<void(int, int, utility::enums::Direction)>&& callback);
    /// @brief Generate a grid using the Wave Function Collapse Algorithm
    /// @param width Grid width
    /// @param height Grid height
    /// @param depth Grid depth
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void waveFunctionCollapseGeneration(int width, int height, int depth, bool invokeAfterGeneration, std::function<void(int, int, int, utility::enums::Direction)>&& callback);
    /// @brief Generate a maze using the passed in algorithm
    /// @param width Width of grid
    /// @param height Height of grid
    /// @param invokeAferGeneration If true callback will only be called after all nodes are generated
    /// @param algorithm Algorithm that will be used to generate maze
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void generateMaze(int width, int height, bool invokeAferGeneration, MazeAlgorithm algorithm, std::function<void(int x, int y, maze_generation::NodeValue adjacentNodes)>&& callback);
    /// @brief Generate a Growing Tree maze using a custom selection callback
    /// @param width Width of grid
    /// @param height Height of grid
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param nodeCallback Callback used to select a node from pending growing tree nodes
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void generateGrowingTreeWithCustomSelection(int width, int height, bool invokeAfterGeneration, std::function<int(int)>&& nodeCallback, std::function<void(int x, int y, maze_generation::NodeValue adjacentNodes)>&& callback);
    /// @brief Geneate maze using Blobby Division Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param regionThreshold User defined region threshold
    /// @param callback Callback when a node is generated
    PCG_ENGINE_CPP_API_API void generateBlobbyDivisionWithCustomRegionThreshold(int width, int height, bool invokeAfterGeneration, int regionThreshold, std::function<void(int x, int y, maze_generation::NodeValue adjacentNodes)>&& callback);
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
    /// @brief Generate a sequence starting from node
    /// @param node First node in sequence
    PCG_ENGINE_CPP_API_API void generateSequence(combination_generation::ISequenceNode& node);
    /// @brief Generate a sequence starting from node with a max number of nodes
    /// @param node First node in sequence
    /// @param count Max number of node in sequence
    /// @param callback Callback when node is added to sequence
    PCG_ENGINE_CPP_API_API void generateSequence(combination_generation::ISequenceNode& node, int count, std::function<void(combination_generation::ISequenceNode*)>&& callback);
}

#endif // PCG_ENGINE_CPP_API_API_HPP
