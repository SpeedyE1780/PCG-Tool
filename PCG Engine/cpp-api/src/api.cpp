#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/cpp-api/api.hpp>

#include <pcg/engine/level-generation/SimpleGeneration.hpp>
#include <pcg/engine/level-generation/MultiDimensionalGeneration.hpp>
#include <pcg/engine/level-generation/WaveFunctionCollapse.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/AldousBroder.hpp>
#include <pcg/engine/maze-generation/BinaryTree.hpp>
#include <pcg/engine/maze-generation/Eller.hpp>
#include <pcg/engine/maze-generation/GrowingTree.hpp>
#include <pcg/engine/maze-generation/HuntAndKill.hpp>
#include <pcg/engine/maze-generation/Kruskal.hpp>
#include <pcg/engine/maze-generation/Prim.hpp>
#include <pcg/engine/maze-generation/RecursiveBacktracker.hpp>
#include <pcg/engine/maze-generation/RecursiveDivision.hpp>
#include <pcg/engine/maze-generation/Sidewinder.hpp>
#include <pcg/engine/maze-generation/Wilson.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::cpp_api
{
    void setSeed(unsigned int seed)
    {
        math::Random::updateSeed(seed);
    }

    void setRandomGenerator(std::function<void(unsigned int)>&& seed, std::function<int(int, int)>&& generate)
    {
        math::Random::initializeRandom(seed, generate);
    }

    void setLoggingFunction(std::function<void(const char*)>&& logFunction)
    {
        utility::setLoggingFunction(logFunction);
    }

    void simpleGeneration(const level_generation::GenerationData& data, math::Axis axis, std::function<void(math::Vector3)>&& callback)
    {
        level_generation::simpleGeneration(data, axis, callback);
    }

    void multiDimensionGeneration(const level_generation::GenerationData& data, math::Axis axes, bool disableOverlap, std::function<void(math::Vector3)>&& callback)
    {
        std::vector<const math::Vector3*> directions = math::getUnitVectors(axes);

        if (directions.empty())
        {
            return;
        }

        level_generation::multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void waveFunctionCollapseGeneration(const level_generation::GenerationData& data, level_generation::ExpansionMode mode, math::Axis axes, std::function<void(math::Vector3, utility::enums::Direction)>&& callback)
    {
        level_generation::waveFunctionCollapse(data, mode, axes, callback);
    }

    void generateMaze(int width, int height, bool invokeAferGeneration, MazeAlgorithm algorithm, std::function<void(int x, int y, utility::enums::Direction neighbors)>&& callback)
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
        case MazeAlgorithm::recursiveDivision:
        {
            maze_generation::recursiveDivision(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::kruskal:
        {
            maze_generation::kruskal(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::prim:
        {
            maze_generation::prim(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::growingTreeOldest:
        {
            maze_generation::growingTree(width, height, invokeAferGeneration, maze_generation::GrowingTreeSelectionMethod::oldest, callback);
            break;
        }
        case MazeAlgorithm::growingTreeMiddle:
        {
            maze_generation::growingTree(width, height, invokeAferGeneration, maze_generation::GrowingTreeSelectionMethod::middle, callback);
            break;
        }
        default:
            break;
        }
    }

    void generateCombination(int elementCount, std::function<void(int, bool)>&& callback)
    {
        combination_generation::generateCombination(elementCount, callback);
    }

    void generateCombination(int elementCount, int minimumElementCount, std::function<void(int, bool)>&& callback)
    {
        combination_generation::generateCombination(elementCount, minimumElementCount, callback);
    }

    void generateCombination(int elementCount, const std::vector<int>& activeElementsIndex, std::function<void(int, bool)>&& callback)
    {
        combination_generation::generateCombination(elementCount, activeElementsIndex, callback);
    }
}

