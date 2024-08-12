#include <pcg/engine/c-api/api.hpp>

#include <pcg/engine/combination-generation/CombinationGenerator.hpp>
#include <pcg/engine/combination-generation/SequenceGenerator.hpp>

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

#include <memory>

namespace pcg::engine::c_api
{
    namespace
    {
        class SequenceNodeWrapper : public combination_generation::ISequenceNode
        {
        public:
            SequenceNodeWrapper(int nodeCount) : possibilitiesCount(nodeCount) { }

            virtual void setNext(int nextNodeIndex) override
            {
                nextNode = nextNodeIndex;
                next = std::make_unique<SequenceNodeWrapper>(updateSequence(nextNodeIndex));
            }

            virtual int getNextCount() const override
            {
                //Dirty fix to invoke update sequence on last node in sequence
                if (possibilitiesCount <= 0)
                {
                    updateSequence(-1);
                }

                return possibilitiesCount;
            }
            virtual ISequenceNode* getNext() const override { return next.get(); }
            virtual ISequenceNode* getNextAt(int index) const override
            {
                next = std::make_unique<SequenceNodeWrapper>(updateSequence(index));
                return next.get();
            }
            virtual void generateSequence() const override { }

            static void setCallbacks(updateSequence get) { updateSequence = get; }
            static void resetCallbacks() { updateSequence = nullptr; }

        private:
            static updateSequence updateSequence;
            int possibilitiesCount;
            int nextNode = -1;
            mutable std::unique_ptr<SequenceNodeWrapper> next = nullptr;
        };

        updateSequence SequenceNodeWrapper::updateSequence = nullptr;
    }

    void setSeed(unsigned int seed)
    {
        math::Random::updateSeed(seed);
    }

    void resetSeed()
    {
        math::Random::resetSeed();
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
        level_generation::multiDimensionalGeneration(data, axes, disableOverlap, callback);
    }

    void waveFunctionCollapseGeneration(const level_generation::GenerationData& data, level_generation::ExpansionMode mode, math::Axis axes, addWFCNodeCallback callback)
    {
        level_generation::waveFunctionCollapse(data, mode, axes, callback);
    }

    void waveFunctionCollapseGridGeneration(int width, int height, math::Axis axes, bool invokeAfterGeneration, addWFCGridNodeCallback callback)
    {
        level_generation::waveFunctionCollapse(width, height, axes, invokeAfterGeneration, callback);
    }

    void waveFunctionCollapse3DGridGeneration(int width, int height, int depth, bool invokeAfterGeneration, addWFC3DGridNodeCallback callback)
    {
        level_generation::waveFunctionCollapse(width, height, depth, invokeAfterGeneration, callback);
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
        case MazeAlgorithm::growingTreeNewest:
        {
            maze_generation::growingTree(width, height, invokeAferGeneration, maze_generation::GrowingTreeSelectionMethod::newest, callback);
            break;
        }
        case MazeAlgorithm::growingTreeRandom:
        {
            maze_generation::growingTree(width, height, invokeAferGeneration, maze_generation::GrowingTreeSelectionMethod::random, callback);
            break;
        }
        case MazeAlgorithm::blobbyDivisionCorridors:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::corridors, callback);
            break;
        }
        case MazeAlgorithm::blobbyDivisionSmall:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::small, callback);
            break;
        }
        case MazeAlgorithm::blobbyDivisionMedium:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::medium, callback);
            break;
        }
        case MazeAlgorithm::blobbyDivisionLarge:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::large, callback);
            break;
        }
        case MazeAlgorithm::blobbyDivisionHuge:
        {
            maze_generation::blobbyDivision(width, height, invokeAferGeneration, maze_generation::SubRegionSize::huge, callback);
            break;
        }
        default:
            break;
        }
    }

    void generateGrowingTreeWithCustomSelection(int width, int height, bool invokeAfterGeneration, selectNodeCallback nodeCallback, addMazeNodeCallback callback)
    {
        maze_generation::growingTree(width, height, invokeAfterGeneration, nodeCallback, callback);
    }

    void generateBlobbyDivisionWithCustomRegionThreshold(int width, int height, bool invokeAfterGeneration, int regionThreshold, addMazeNodeCallback callback)
    {
        maze_generation::blobbyDivision(width, height, invokeAfterGeneration, regionThreshold, callback);
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

    void generateSequence(int nextNodeCount, updateSequence updateSequence)
    {
        SequenceNodeWrapper::setCallbacks(updateSequence);
        SequenceNodeWrapper wrappedNode(nextNodeCount);
        combination_generation::generateSequence(wrappedNode);
        SequenceNodeWrapper::resetCallbacks();
    }

    void generateCyclicSequence(int nextNodeCount, int sequenceLength, updateSequence updateSequence)
    {
        SequenceNodeWrapper::setCallbacks(updateSequence);
        SequenceNodeWrapper wrappedNode(nextNodeCount);
        combination_generation::generateSequence(wrappedNode, sequenceLength);
        SequenceNodeWrapper::resetCallbacks();
    }
}
