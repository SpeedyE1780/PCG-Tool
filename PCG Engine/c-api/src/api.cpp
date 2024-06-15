#include <pcg/engine/c-api/api.hpp>

#include <pcg/engine/level-generation/SimpleGeneration.hpp>
#include <pcg/engine/level-generation/MultiDimensionalGeneration.hpp>
#include <pcg/engine/level-generation/WaveFunctionCollapse.hpp>

#include <pcg/engine/maze/AldousBroder.hpp>
#include <pcg/engine/maze/BinaryTree.hpp>
#include <pcg/engine/maze/Sidewinder.hpp>
#include <pcg/engine/maze/Wilson.hpp>

namespace pcg::engine::c_api
{
    void setSeed(unsigned int seed)
    {
        math::Random::seed(seed);
    }

    void setRandomGenerator(setSeedCallback seed, generateNumberCallback generate)
    {
        return math::initializeRandom(seed, generate);
    }

    void setLoggingFunction(logMessage logFunction)
    {
        utility::setLoggingFunction(logFunction);
    }

    void simpleGeneration(level_generation::GenerationData* data, math::axis::Flag axis, math::Direction direction, addPointCallback callback)
    {
        level_generation::simpleGeneration(data, axis, direction, callback);
    }

    void multiDimensionGeneration(level_generation::GenerationData* data, math::axis::Flag axis, bool disableOverlap, addPointCallback callback)
    {
        std::vector<const math::Vector3*> directions = math::getUnitVectors(axis);

        if (directions.empty())
        {
            return;
        }

        level_generation::multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void waveFunctionCollapseGeneration(level_generation::GenerationData* data, level_generation::ExpansionMode mode, math::axis::Flag axis, addWFCPointCallback callback)
    {
        level_generation::waveFunctionCollapse(data, mode, axis, callback);
    }

    void generateMaze(int width, int height, maze::MazeAlgorithm algorithm, addMazePointCallback callback)
    {
        switch (algorithm)
        {
        case maze::MazeAlgorithm::aldousBroder:
        {
            maze::aldousBroder(width, height, callback);
            break;
        }
        case maze::MazeAlgorithm::wilson:
        {
            maze::wilson(width, height, callback);
            break;
        }
        case maze::MazeAlgorithm::binaryTreeNE:
        {
            maze::binaryTree(width, height, maze::Diagonal::NE, callback);
            break;
        }
        case maze::MazeAlgorithm::binaryTreeNW:
        {
            maze::binaryTree(width, height, maze::Diagonal::NW, callback);
            break;
        }
        case maze::MazeAlgorithm::binaryTreeSE:
        {
            maze::binaryTree(width, height, maze::Diagonal::SE, callback);
            break;
        }
        case maze::MazeAlgorithm::binaryTreeSW:
        {
            maze::binaryTree(width, height, maze::Diagonal::SW, callback);
            break;
        }
        case maze::MazeAlgorithm::sidewinder:
        {
            maze::sidewinder(width, height, callback);
            break;
        }
        default:
            break;
        }
    }
}
