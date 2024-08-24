#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/cpp-api/api.hpp>

#include <pcg/engine/level-generation/SimpleGeneration.hpp>
#include <pcg/engine/level-generation/MultiDimensionalGeneration.hpp>
#include <pcg/engine/level-generation/WaveFunctionCollapse.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze-generation/AldousBroder.hpp>
#include <pcg/engine/maze-generation/BinaryTree.hpp>
#include <pcg/engine/maze-generation/BlobbyDivision.hpp>
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

    void resetSeed()
    {
        math::Random::resetSeed();
    }

    void setRandomGenerator(std::function<void(unsigned int)>&& seed, std::function<int(int, int)>&& generate)
    {
        math::Random::initializeRandom(std::move(seed), std::move(generate));
    }

    void setLoggingFunction(std::function<void(const char*)>&& logFunction)
    {
        utility::setLoggingFunction(std::move(logFunction));
    }

    void simpleGeneration(const level_generation::GenerationData& data, const math::Vector3& offset, std::function<void(math::Vector3)>&& callback)
    {
        level_generation::simpleGeneration(data, offset, std::move(callback));
    }

    void multiDimensionGeneration(const level_generation::GenerationData& data, math::Axis axes, bool disableOverlap, std::function<void(math::Vector3)>&& callback)
    {
        level_generation::multiDimensionalGeneration(data, axes, disableOverlap, std::move(callback));
    }

    void waveFunctionCollapseGeneration(const level_generation::GenerationData& data, level_generation::ExpansionMode mode, math::Axis axes, std::function<void(math::Vector3, utility::enums::Direction)>&& callback)
    {
        level_generation::waveFunctionCollapse(data, mode, axes, std::move(callback));
    }

    void waveFunctionCollapseGeneration(int width, int height, math::Axis axes, bool invokeAfterGeneration, std::function<void(int, int, utility::enums::Direction)>&& callback)
    {
        level_generation::waveFunctionCollapse(width, height, axes, invokeAfterGeneration, std::move(callback));
    }

    void waveFunctionCollapseGeneration(int width, int height, int depth, bool invokeAfterGeneration, std::function<void(int, int, int, utility::enums::Direction)>&& callback)
    {
        level_generation::waveFunctionCollapse(width, height, depth, invokeAfterGeneration, std::move(callback));
    }

    void generateMaze(int width, int height, bool invokeAferGeneration, MazeAlgorithm algorithm, std::function<void(int x, int y, maze_generation::NodeValue adjacentNodes)>&& callback)
    {
        switch (algorithm)
        {
        case MazeAlgorithm::aldousBroder:
        {
            maze_generation::aldousBroder(width, height, invokeAferGeneration, std::move(callback));
            break;
        }
        case MazeAlgorithm::wilson:
        {
            maze_generation::wilson(width, height, invokeAferGeneration, std::move(callback));
            break;
        }
        case MazeAlgorithm::binaryTreeNE:
        {
            maze_generation::binaryTree(width, height, invokeAferGeneration, maze_generation::Diagonal::NE, std::move(callback));
            break;
        }
        case MazeAlgorithm::binaryTreeNW:
        {
            maze_generation::binaryTree(width, height, invokeAferGeneration, maze_generation::Diagonal::NW, std::move(callback));
            break;
        }
        case MazeAlgorithm::binaryTreeSE:
        {
            maze_generation::binaryTree(width, height, invokeAferGeneration, maze_generation::Diagonal::SE, std::move(callback));
            break;
        }
        case MazeAlgorithm::binaryTreeSW:
        {
            maze_generation::binaryTree(width, height, invokeAferGeneration, maze_generation::Diagonal::SW, std::move(callback));
            break;
        }
        case MazeAlgorithm::sidewinder:
        {
            maze_generation::sidewinder(width, height, invokeAferGeneration, std::move(callback));
            break;
        }
        case MazeAlgorithm::eller:
        {
            maze_generation::eller(width, height, invokeAferGeneration, std::move(callback));
            break;
        }
        case MazeAlgorithm::huntAndKill:
        {
            maze_generation::huntAndKill(width, height, invokeAferGeneration, std::move(callback));
            break;
        }
        case MazeAlgorithm::recursiveBacktracker:
        {
            maze_generation::recursiveBacktracker(width, height, invokeAferGeneration, std::move(callback));
            break;
        }
        case MazeAlgorithm::recursiveDivision:
        {
            maze_generation::recursiveDivision(width, height, invokeAferGeneration, std::move(callback));
            break;
        }
        case MazeAlgorithm::kruskal:
        {
            maze_generation::kruskal(width, height, invokeAferGeneration, std::move(callback));
            break;
        }
        case MazeAlgorithm::prim:
        {
            maze_generation::prim(width, height, invokeAferGeneration, std::move(callback));
            break;
        }
        case MazeAlgorithm::growingTreeOldest:
        {
            maze_generation::growingTree(width, height, invokeAferGeneration, maze_generation::GrowingTreeSelectionMethod::oldest, std::move(callback));
            break;
        }
        case MazeAlgorithm::growingTreeMiddle:
        {
            maze_generation::growingTree(width, height, invokeAferGeneration, maze_generation::GrowingTreeSelectionMethod::middle, std::move(callback));
            break;
        }
        case MazeAlgorithm::growingTreeNewest:
        {
            maze_generation::growingTree(width, height, invokeAferGeneration, maze_generation::GrowingTreeSelectionMethod::newest, std::move(callback));
            break;
        }
        case MazeAlgorithm::growingTreeRandom:
        {
            maze_generation::growingTree(width, height, invokeAferGeneration, maze_generation::GrowingTreeSelectionMethod::random, std::move(callback));
            break;
        }
        case MazeAlgorithm::blobbyDivisionCorridors:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::corridors, std::move(callback));
            break;
        }
        case MazeAlgorithm::blobbyDivisionSmall:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::small, std::move(callback));
            break;
        }
        case MazeAlgorithm::blobbyDivisionMedium:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::medium, std::move(callback));
            break;
        }
        case MazeAlgorithm::blobbyDivisionLarge:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::large, std::move(callback));
            break;
        }
        case MazeAlgorithm::blobbyDivisionHuge:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::huge, std::move(callback));
            break;
        }
        default:
            break;
        }
    }

    void generateGrowingTreeWithCustomSelection(int width, int height, bool invokeAfterGeneration, std::function<int(int)>&& nodeCallback, std::function<void(int x, int y, maze_generation::NodeValue adjacentNodes)>&& callback)
    {
        maze_generation::growingTree(width, height, invokeAfterGeneration, std::move(nodeCallback), std::move(callback));
    }

    void generateBlobbyDivisionWithCustomRegionThreshold(int width, int height, bool invokeAfterGeneration, int regionThreshold, std::function<void(int x, int y, maze_generation::NodeValue adjacentNodes)>&& callback)
    {
        maze_generation::blobbyDivision(width, height, invokeAfterGeneration, regionThreshold, std::move(callback));
    }

    void generateCombination(int elementCount, std::function<void(int, bool)>&& callback)
    {
        combination_generation::generateCombination(elementCount, std::move(callback));
    }

    void generateCombination(int elementCount, int minimumElementCount, std::function<void(int, bool)>&& callback)
    {
        combination_generation::generateCombination(elementCount, minimumElementCount, std::move(callback));
    }

    void generateCombination(int elementCount, const std::vector<int>& activeElementsIndex, std::function<void(int, bool)>&& callback)
    {
        combination_generation::generateCombination(elementCount, activeElementsIndex, std::move(callback));
    }

    void generateSequence(combination_generation::ISequenceNode& node)
    {
        combination_generation::generateSequence(node);
    }

    void generateSequence(combination_generation::ISequenceNode& node, int count, std::function<void(combination_generation::ISequenceNode*)>&& callback)
    {
        return combination_generation::generateSequence(node, count, std::move(callback));
    }
}
