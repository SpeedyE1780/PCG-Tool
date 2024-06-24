#include <pcg/engine/c-api/api.hpp>

#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/level-generation/SimpleGeneration.hpp>
#include <pcg/engine/level-generation/MultiDimensionalGeneration.hpp>
#include <pcg/engine/level-generation/WaveFunctionCollapse.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/AldousBroder.hpp>
#include <pcg/engine/maze-generation/BinaryTree.hpp>
#include <pcg/engine/maze-generation/Eller.hpp>
#include <pcg/engine/maze-generation/HuntAndKill.hpp>
#include <pcg/engine/maze-generation/RecursiveBacktracker.hpp>
#include <pcg/engine/maze-generation/Sidewinder.hpp>
#include <pcg/engine/maze-generation/Wilson.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::c_api
{
    void setSeed(unsigned int seed)
    {
        math::Random::updateSeed(seed);
    }

    void setRandomGenerator(setSeedCallback seed, generateNumberCallback generate)
    {
        math::Random::initializeRandom(seed, generate);
    }

    void setLoggingFunction(logMessage logFunction)
    {
        utility::setLoggingFunction(logFunction);
    }

    void simpleGeneration(const level_generation::GenerationData& data, math::Axis axis, addNodeCallback callback)
    {
        level_generation::simpleGeneration(data, axis, callback);
    }

    void multiDimensionGeneration(const level_generation::GenerationData& data, math::Axis axes, bool disableOverlap, addNodeCallback callback)
    {
        std::vector<const math::Vector3*> directions = math::getUnitVectors(axes);

        if (directions.empty())
        {
            return;
        }

        level_generation::multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void waveFunctionCollapseGeneration(const level_generation::GenerationData& data, level_generation::ExpansionMode mode, math::Axis axes, addWFCNodeCallback callback)
    {
        level_generation::waveFunctionCollapse(data, mode, axes, callback);
    }

    void generateMaze(int width, int height, bool invokeAferGeneration, MazeAlgorithm algorithm, addMazeNodeCallback callback)
    {
        switch (algorithm)
        {
        case MazeAlgorithm::aldousBroder:
        {
            maze_generation::aldousBroder(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::wilson:
        {
            maze_generation::wilson(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::binaryTreeNE:
        {
            maze_generation::binaryTree(width, height, invokeAferGeneration, maze_generation::Diagonal::NE, callback);
            break;
        }
        case MazeAlgorithm::binaryTreeNW:
        {
            maze_generation::binaryTree(width, height, invokeAferGeneration, maze_generation::Diagonal::NW, callback);
            break;
        }
        case MazeAlgorithm::binaryTreeSE:
        {
            maze_generation::binaryTree(width, height, invokeAferGeneration, maze_generation::Diagonal::SE, callback);
            break;
        }
        case MazeAlgorithm::binaryTreeSW:
        {
            maze_generation::binaryTree(width, height, invokeAferGeneration, maze_generation::Diagonal::SW, callback);
            break;
        }
        case MazeAlgorithm::sidewinder:
        {
            maze_generation::sidewinder(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::eller:
        {
            maze_generation::eller(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::huntAndKill:
        {
            maze_generation::huntAndKill(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::recursiveBacktracker:
        {
            maze_generation::recursiveBacktracker(width, height, invokeAferGeneration, callback);
            break;
        }
        default:
            break;
        }
    }

    void generateCombination(int elementCount, generateCombinationCallback callback)
    {
        combination_generation::generateCombination(elementCount, callback);
    }

    void generateCombinationWithMinimumElementCount(int elementCount, int minimumElementCount, generateCombinationCallback callback)
    {
        combination_generation::generateCombination(elementCount, minimumElementCount, callback);
    }

    void generateCombinationWithActiveElements(int elementCount, int* activeElementsIndex, int activeElementsCount, generateCombinationCallback callback)
    {
        std::vector<int> activeElements(activeElementsCount);

        for (int i = 0; i < activeElementsCount; ++i)
        {
            activeElements[i] = activeElementsIndex[i];
        }

        combination_generation::generateCombination(elementCount, activeElements, callback);
    }
}
