#ifndef PCG_ENGINE_C_API_API_HPP
#define PCG_ENGINE_C_API_API_HPP

#include <pcg/engine/c-api/config.hpp>

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/Vector3.hpp>
#include <pcg/engine/math/Vector4.hpp>

#include <pcg/engine/maze-generation/Common.hpp>

#include <pcg/engine/utility/Enums.hpp>

namespace pcg::engine::c_api
{
    /// @brief Callback to indicate that a node was spawned at position
    typedef void (*addNodeCallback)(math::Vector3 position);
    /// @brief Callback to indicate that a node was spawned at this position and has these adjacent node
    typedef void (*addWFCNodeCallback)(math::Vector3 position, utility::enums::Direction adjacentNodes);
    /// @brief Callback to indicate that a node was spawned at this position and has these adjacent node
    typedef void (*addWFC4DNodeCallback)(math::Vector4 position, utility::enums::Direction adjacentNodes);
    /// @brief Callback to indicate that a node was spawned at x, y coordinates and has these adjacent node
    typedef void (*addWFCGridNodeCallback)(int x, int y, utility::enums::Direction adjacentNodes);
    /// @brief Callback to indicate that a node was spawned at x, y, z coordinates and has these adjacent node
    typedef void (*addWFC3DGridNodeCallback)(int x, int y, int z, utility::enums::Direction adjacentNodes);
    /// @brief Callback to indicate that a node was spawned at the x, y coordinate and has these adjacent node
    typedef void (*addMazeNodeCallback)(int x, int y, maze_generation::NodeValue adjacentNodes);
    /// @brief Callback to select node during growing tree maze generation with user defined function
    typedef int (*selectNodeCallback)(int size);
    /// @brief Function that will be used when setting the random number generator's seed
    typedef void (*setSeedCallback)(unsigned int seed);
    /// @brief Function used to generate a number between [min, max[
    typedef int (*generateNumberCallback)(int minimum, int maximum);
    /// @brief Callback to add element to generated set
    typedef void (*generateCombinationCallback)(int elementIndex, bool included);
    /// @brief Function used to log message from the engine
    typedef void (*logMessage)(const char* message);
    /// @brief Function used to add next node in sequence and returns next node possibility count
    typedef int (*updateSequence)(int index);

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
    PCG_ENGINE_C_API_API void setSeed(unsigned int seed);
    /// @brief Reset RNG seed
    PCG_ENGINE_C_API_API void resetSeed();
    /// @brief Set functions used to set seed and generate numbers
    /// @param seed Function that will set the RNG seed
    /// @param generate Function used to generate numbers
    PCG_ENGINE_C_API_API void setRandomGenerator(setSeedCallback seed, generateNumberCallback generate);
    /// @brief Set function used to log messages from the engine
    /// @param logFunction Function that will log engine messages
    PCG_ENGINE_C_API_API void setLoggingFunction(logMessage logFunction);
    /// @brief Generate a linear level on a single axis
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param offset Offset between nodes
    /// @param callback Callback when a node is generated
    PCG_ENGINE_C_API_API void simpleGeneration(const level_generation::GenerationData& data, const math::Vector3& offset, addNodeCallback callback);
    /// @brief Generate a level on multiple axes
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param axes Axes flag indicating which axes are being used
    /// @param disableOverlap If true nodes cannot be generated on top of one another
    /// @param callback Callback when a node is generated
    PCG_ENGINE_C_API_API void multiDimensionGeneration(const level_generation::GenerationData& data, math::Axis axes, bool disableOverlap, addNodeCallback callback);
    /// @brief Generate a level using the Wave Function Collapse Algorithm
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param mode If Breadth-First Search (BFS) or Depth-First Search (DFS) expansion should be used
    /// @param axes Axes flag indicating which axes are being used
    /// @param callback Callback when a node is generated
    PCG_ENGINE_C_API_API void waveFunctionCollapseGeneration(const level_generation::GenerationData& data, level_generation::ExpansionMode mode, math::Axis axes, addWFCNodeCallback callback);
    /// @brief Generate a 4D level using the Wave Function Collapse Algorithm
    /// @param data Object containing number of nodes that need to be generated, node size & starting position
    /// @param mode If Breadth-First Search (BFS) or Depth-First Search (DFS) expansion should be used
    /// @param axes Axes flag indicating which axes are being used
    /// @param callback Callback when a node is generated
    PCG_ENGINE_C_API_API void waveFunctionCollapse4DGeneration(const level_generation::GenerationData& data, level_generation::ExpansionMode mode, math::Axis axes, addWFC4DNodeCallback callback);
    /// @brief Generate a grid using the Wave Function Collapse Algorithm
    /// @param width Grid width
    /// @param height Grid height
    /// @param plane Plane indicating on which plane is the grid being spawned
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param callback Callback when a node is generated
    PCG_ENGINE_C_API_API void waveFunctionCollapseGridGeneration(int width, int height, math::Plane plane, bool invokeAfterGeneration, addWFCGridNodeCallback callback);
    /// @brief Generate a grid using the Wave Function Collapse Algorithm
    /// @param width Grid width
    /// @param height Grid height
    /// @param depth Grid depth
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param callback Callback when a node is generated
    PCG_ENGINE_C_API_API void waveFunctionCollapse3DGridGeneration(int width, int height, int depth, bool invokeAfterGeneration, addWFC3DGridNodeCallback callback);
    /// @brief Generate a maze using the passed in algorithm
    /// @param width Grid width
    /// @param height Grid Height
    /// @param invokeAferGeneration If true callback will only be called after all nodes are generated
    /// @param algorithm Algorithm that will be used to generate maze
    /// @param callback Callback when a node is generated
    PCG_ENGINE_C_API_API void generateMaze(int width, int height, bool invokeAferGeneration, MazeAlgorithm algorithm, addMazeNodeCallback callback);
    /// @brief Generate a Growing Tree maze using a custom selection callback
    /// @param width Grid width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param nodeCallback Callback used to select a node from pending growing tree nodes
    /// @param callback Callback when a node is generated
    PCG_ENGINE_C_API_API void generateGrowingTreeWithCustomSelection(int width, int height, bool invokeAfterGeneration, selectNodeCallback nodeCallback, addMazeNodeCallback callback);
    /// @brief Geneate maze using Blobby Division Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param regionThreshold User defined region threshold
    /// @param callback Callback when a node is generated
    PCG_ENGINE_C_API_API void generateBlobbyDivisionWithCustomRegionThreshold(int width, int height, bool invokeAfterGeneration, int regionThreshold, addMazeNodeCallback callback);
    /// @brief Generate a combination given a number of elements
    /// @param elementCount Number of element that are available in set
    /// @param callback Callback to add element to generated set
    PCG_ENGINE_C_API_API void generateCombination(int elementCount, generateCombinationCallback callback);
    /// @brief Generate a combination with at least minimumElementCount elements
    /// @param elementCount Number of element that are available in set
    /// @param minimumElementCount Minimum number of elements in set
    /// @param callback Callback to add element to generated set
    PCG_ENGINE_C_API_API void generateCombinationWithMinimumElementCount(int elementCount, int minimumElementCount, generateCombinationCallback callback);
    /// @brief Generate a combination with the given elements active
    /// @param elementCount Number of element that are available in set
    /// @param activeElementsIndex Array of elements that must be included
    /// @param activeElementsCount Number of elements in activeElementsIndex array
    /// @param callback Callback to add element to generated set
    PCG_ENGINE_C_API_API void generateCombinationWithActiveElements(int elementCount, int* activeElementsIndex, int activeElementsCount, generateCombinationCallback callback);
    /// @brief Generate a sequence starting from node
    /// @param nextNodeCount Count of next nodes from first node in sequence
    /// @param updateSequence Callback to add next node in sequence and returns next node possibility count
    PCG_ENGINE_C_API_API void generateSequence(int nextNodeCount, updateSequence updateSequence);
    /// @brief Generate a sequence starting from node
    /// @param nextNodeCount Count of next nodes from first node in sequence
    /// @param sequenceLength Length of generated sequence
    /// @param updateSequence Callback to add next node in sequence and returns next node possibility count
    PCG_ENGINE_C_API_API void generateCyclicSequence(int nextNodeCount, int sequenceLength, updateSequence updateSequence);
}

#endif // PCG_ENGINE_C_API_API_HPP
