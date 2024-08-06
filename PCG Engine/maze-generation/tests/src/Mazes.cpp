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

#include <gtest/gtest.h>

#include <functional>
#include <fstream>
#include <sstream>

namespace pcg::engine::maze_generation::tests
{
    namespace
    {
        void binaryTreeNE(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            binaryTree(width, height, invokeAfterGeneration, Diagonal::NE, std::move(callback));
        }

        void binaryTreeNW(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            binaryTree(width, height, invokeAfterGeneration, Diagonal::NW, std::move(callback));
        }

        void binaryTreeSE(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            binaryTree(width, height, invokeAfterGeneration, Diagonal::SE, std::move(callback));
        }

        void binaryTreeSW(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            binaryTree(width, height, invokeAfterGeneration, Diagonal::SW, std::move(callback));
        }

        void blobbyDivisionCorridors(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::corridors, std::move(callback));
        }

        void blobbyDivisionSmall(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::small, std::move(callback));
        }

        void blobbyDivisionMedium(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::medium, std::move(callback));
        }

        void blobbyDivisionLarge(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::large, std::move(callback));
        }

        void blobbyDivisionHuge(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::huge, std::move(callback));
        }

        void growingTreeOldest(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            growingTree(width, height, invokeAfterGeneration, GrowingTreeSelectionMethod::oldest, std::move(callback));
        }

        void growingTreeMiddle(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            growingTree(width, height, invokeAfterGeneration, GrowingTreeSelectionMethod::middle, std::move(callback));
        }

        void growingTreeNewest(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            growingTree(width, height, invokeAfterGeneration, GrowingTreeSelectionMethod::newest, std::move(callback));
        }

        void growingTreeRandom(int width, int height, bool invokeAfterGeneration, MazeCallback&& callback)
        {
            growingTree(width, height, invokeAfterGeneration, GrowingTreeSelectionMethod::random, std::move(callback));
        }
    }

    struct MazeParameters
    {
        std::string fileName;
        std::function<void(int, int, bool, MazeCallback&&)> function;
    };

    class MazeAlgorithmTest : public ::testing::TestWithParam<MazeParameters> 
    {
    public:
        struct PrintToStringParamName
        {
            template <class ParamType>
            std::string operator()(const testing::TestParamInfo<ParamType>& info) const
            {
                const auto& mazeParameters = static_cast<MazeParameters>(info.param);
                return mazeParameters.fileName;
            }
        };
    };

    TEST_P(MazeAlgorithmTest, Maze)
    {
        math::Random::resetSeed();

        const auto& [fileName, mazeFunction] = GetParam();
        std::ostringstream oss{};
        oss << "GoldenValues/" << fileName << ".txt";

        std::ifstream input(oss.str());

        std::function<void(int, int, NodeValue)> callback = [&input](int x, int y, NodeValue value)
            {
                int goldenX = 0;
                int goldenY = 0;
                int goldenValue = 0;
                input >> goldenX >> goldenY >> goldenValue;

                EXPECT_EQ(goldenX, x);
                EXPECT_EQ(goldenY, y);
                EXPECT_EQ(goldenValue, static_cast<int>(value));
            };

        mazeFunction(20, 20, false, callback);

        input.close();
    }

    INSTANTIATE_TEST_CASE_P(
        MazeAlgorithmTests,
        MazeAlgorithmTest,
        ::testing::Values(
            MazeParameters{ "AldousBroder", aldousBroder },
            MazeParameters{ "BinaryTreeNE", binaryTreeNE },
            MazeParameters{ "BinaryTreeNW", binaryTreeNW },
            MazeParameters{ "BinaryTreeSE", binaryTreeSE },
            MazeParameters{ "BinaryTreeSW", binaryTreeSW },
            MazeParameters{ "BlobbyDivisionCorridors", blobbyDivisionCorridors },
            MazeParameters{ "BlobbyDivisionSmall", blobbyDivisionSmall },
            MazeParameters{ "BlobbyDivisionMedium", blobbyDivisionMedium },
            MazeParameters{ "BlobbyDivisionLarge", blobbyDivisionLarge },
            MazeParameters{ "BlobbyDivisionHuge", blobbyDivisionHuge },
            MazeParameters{ "Eller", eller },
            MazeParameters{ "GrowingTreeOldest", growingTreeOldest },
            MazeParameters{ "GrowingTreeMiddle", growingTreeMiddle },
            MazeParameters{ "GrowingTreeNewest", growingTreeNewest },
            MazeParameters{ "GrowingTreeRandom", growingTreeRandom },
            MazeParameters{ "HuntAndKill", huntAndKill },
            MazeParameters{ "Kruskal", kruskal },
            MazeParameters{ "Prim", prim },
            MazeParameters{ "RecursiveBacktracker", recursiveBacktracker },
            MazeParameters{ "RecursiveDivision", recursiveDivision },
            MazeParameters{ "Sidewinder", sidewinder },
            MazeParameters{ "Wilson", wilson }
        ),
    MazeAlgorithmTest::PrintToStringParamName());
}
