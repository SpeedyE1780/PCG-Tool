#include <pcg/engine/core/SimpleGeneration.hpp>
#include <pcg/engine/core/MultiDimensionalGeneration.hpp>
#include <pcg/engine/core/WaveFunctionCollapse.hpp>

#include <pcg/engine/cpp-api/api.hpp>

namespace pcg::engine::cpp_api
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

    void generation1D(core::GenerationData* data, math::Axis axis, math::Direction direction, core::addPointCallback callback)
    {
        core::simpleGeneration(data, axis, direction, callback);
    }

    void generation2D(core::GenerationData* data, math::Plane plane, bool disableOverlap, core::addPointCallback callback)
    {
        std::vector<const math::Vector3*> directions = getPlaneUnitVectors(plane);

        if (directions.empty())
        {
            return;
        }

        core::multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void generation3D(core::GenerationData* data, bool disableOverlap, core::addPointCallback callback)
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

    void generateMaze(int width, int height, core::MazeAlgorithm algorithm, core::addMazePointCallback callback)
    {
        switch (algorithm)
        {
        case core::MazeAlgorithm::aldousBroder:
        {
            core::aldousBroder(width, height, callback);
            break;
        }
        case core::MazeAlgorithm::wilson:
        {
            core::wilson(width, height, callback);
            break;
        }
        case core::MazeAlgorithm::binaryTreeNE:
        {
            core::binaryTree(width, height, core::Diagonal::NE, callback);
            break;
        }
        case core::MazeAlgorithm::binaryTreeNW:
        {
            core::binaryTree(width, height, core::Diagonal::NW, callback);
            break;
        }
        case core::MazeAlgorithm::binaryTreeSE:
        {
            core::binaryTree(width, height, core::Diagonal::SE, callback);
            break;
        }
        case core::MazeAlgorithm::binaryTreeSW:
        {
            core::binaryTree(width, height, core::Diagonal::SW, callback);
            break;
        }
        case core::MazeAlgorithm::sidewinder:
        {
            core::sidewinder(width, height, callback);
            break;
        }
        default:
            break;
        }
    }
}

