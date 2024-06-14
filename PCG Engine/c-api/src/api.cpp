#include <pcg/engine/c-api/api.hpp>

#include <pcg/engine/core/SimpleGeneration.hpp>
#include <pcg/engine/core/MultiDimensionalGeneration.hpp>
#include <pcg/engine/core/WaveFunctionCollapse.hpp>

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

    void setRandomGenerator(math::setSeed seed, math::generateNumber generate)
    {
        return math::initializeRandom(seed, generate);
    }

    void setLoggingFunction(utility::logMessage logFunction)
    {
        utility::setLoggingFunction(logFunction);
    }

    void generation1D(core::GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback)
    {
        core::simpleGeneration(data, axis, direction, callback);
    }

    void generation2D(core::GenerationData* data, math::Plane plane, bool disableOverlap, addPointCallback callback)
    {
        std::vector<const math::Vector3*> directions = getPlaneUnitVectors(plane);

        if (directions.empty())
        {
            return;
        }

        core::multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void generation3D(core::GenerationData* data, bool disableOverlap, addPointCallback callback)
    {
        static const std::vector<const math::Vector3*> directions
        {
            {
                &math::Vector3::right,
                &math::Vector3::left,
                &math::Vector3::up,
                &math::Vector3::down,
                &math::Vector3::forward,
                &math::Vector3::backward
            }
        };

        multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void waveFunctionCollapseGeneration(core::GenerationData* data, core::ExpansionMode mode, core::addWFCPointCallback callback)
    {
        core::waveFunctionCollapse(data, mode, callback);
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
