#include <pcg/engine/combination-generation/CombinationGenerator.hpp>

#include <pcg/engine/cpp-api/api.hpp>

#include <pcg/engine/level-generation/SimpleGeneration.hpp>
#include <pcg/engine/level-generation/MultiDimensionalGeneration.hpp>
#include <pcg/engine/level-generation/WaveFunctionCollapse.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/maze/AldousBroder.hpp>
#include <pcg/engine/maze/BinaryTree.hpp>
#include <pcg/engine/maze/Sidewinder.hpp>
#include <pcg/engine/maze/Wilson.hpp>

#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::cpp_api
{
    void setSeed(unsigned int seed)
    {
        math::Random::seed(seed);
    }

    void setRandomGenerator(std::function<void(unsigned int)>&& seed, std::function<int(int, int)>&& generate)
    {
        return math::initializeRandom(seed, generate);
    }

    void setLoggingFunction(std::function<void(const char*)>&& logFunction)
    {
        utility::setLoggingFunction(logFunction);
    }

    void simpleGeneration(level_generation::GenerationData* data, math::Axis axis, math::Direction direction, std::function<void(math::Vector3)>&& callback)
    {
        level_generation::simpleGeneration(data, axis, direction, callback);
    }

    void multiDimensionGeneration(level_generation::GenerationData* data, math::Axis axes, bool disableOverlap, std::function<void(math::Vector3)>&& callback)
    {
        std::vector<const math::Vector3*> directions = math::getUnitVectors(axes);

        if (directions.empty())
        {
            return;
        }

        level_generation::multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void waveFunctionCollapseGeneration(level_generation::GenerationData* data, level_generation::ExpansionMode mode, math::Axis axes, std::function<void(math::Vector3, utility::enums::Direction)>&& callback)
    {
        level_generation::waveFunctionCollapse(data, mode, axes, callback);
    }

    void generateMaze(int width, int height, bool invokeAferGeneration, MazeAlgorithm algorithm, std::function<void(int x, int y, utility::enums::Direction neighbors)>&& callback)
    {
        switch (algorithm)
        {
        case MazeAlgorithm::aldousBroder:
        {
            maze::aldousBroder(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::wilson:
        {
            maze::wilson(width, height, invokeAferGeneration, callback);
            break;
        }
        case MazeAlgorithm::binaryTreeNE:
        {
            maze::binaryTree(width, height, invokeAferGeneration, maze::Diagonal::NE, callback);
            break;
        }
        case MazeAlgorithm::binaryTreeNW:
        {
            maze::binaryTree(width, height, invokeAferGeneration, maze::Diagonal::NW, callback);
            break;
        }
        case MazeAlgorithm::binaryTreeSE:
        {
            maze::binaryTree(width, height, invokeAferGeneration, maze::Diagonal::SE, callback);
            break;
        }
        case MazeAlgorithm::binaryTreeSW:
        {
            maze::binaryTree(width, height, invokeAferGeneration, maze::Diagonal::SW, callback);
            break;
        }
        case MazeAlgorithm::sidewinder:
        {
            maze::sidewinder(width, height, invokeAferGeneration, callback);
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

