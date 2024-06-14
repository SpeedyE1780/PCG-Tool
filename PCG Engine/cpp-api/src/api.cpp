#include <pcg/engine/level-generation/SimpleGeneration.hpp>
#include <pcg/engine/level-generation/MultiDimensionalGeneration.hpp>
#include <pcg/engine/level-generation/WaveFunctionCollapse.hpp>

#include <pcg/engine/cpp-api/api.hpp>

#include <pcg/engine/maze/AldousBroder.hpp>
#include <pcg/engine/maze/BinaryTree.hpp>
#include <pcg/engine/maze/Sidewinder.hpp>
#include <pcg/engine/maze/Wilson.hpp>

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

    void generation1D(level_generation::GenerationData* data, math::Axis axis, math::Direction direction, std::function<void(math::Vector3)>&& callback)
    {
        level_generation::simpleGeneration(data, axis, direction, callback);
    }

    void generation2D(level_generation::GenerationData* data, math::Plane plane, bool disableOverlap, std::function<void(math::Vector3)>&& callback)
    {
        std::vector<const math::Vector3*> directions = getPlaneUnitVectors(plane);

        if (directions.empty())
        {
            return;
        }

        level_generation::multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void generation3D(level_generation::GenerationData* data, bool disableOverlap, std::function<void(math::Vector3)>&& callback)
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

    void waveFunctionCollapseGeneration(level_generation::GenerationData* data, level_generation::ExpansionMode mode, std::function<void(math::Vector3, int)>&& callback)
    {
        level_generation::waveFunctionCollapse(data, mode, callback);
    }

    void generateMaze(int width, int height, maze::MazeAlgorithm algorithm, std::function<void(int x, int y, int neighbors)>&& callback)
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

