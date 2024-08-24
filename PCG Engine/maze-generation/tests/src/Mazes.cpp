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
        void binaryTreeNE(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            binaryTree(width, height, invokeAfterGeneration, Diagonal::NE, callback);
        }

        void binaryTreeNW(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            binaryTree(width, height, invokeAfterGeneration, Diagonal::NW, callback);
        }

        void binaryTreeSE(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            binaryTree(width, height, invokeAfterGeneration, Diagonal::SE, callback);
        }

        void binaryTreeSW(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            binaryTree(width, height, invokeAfterGeneration, Diagonal::SW, callback);
        }

        void blobbyDivisionCorridors(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::corridors, callback);
        }

        void blobbyDivisionSmall(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::small, callback);
        }

        void blobbyDivisionMedium(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::medium, callback);
        }

        void blobbyDivisionLarge(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::large, callback);
        }

        void blobbyDivisionHuge(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            blobbyDivision(width, height, invokeAfterGeneration, SubRegionSize::huge, callback);
        }

        void growingTreeOldest(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            growingTree(width, height, invokeAfterGeneration, GrowingTreeSelectionMethod::oldest, callback);
        }

        void growingTreeMiddle(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            growingTree(width, height, invokeAfterGeneration, GrowingTreeSelectionMethod::middle, callback);
        }

        void growingTreeNewest(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            growingTree(width, height, invokeAfterGeneration, GrowingTreeSelectionMethod::newest, callback);
        }

        void growingTreeRandom(int width, int height, bool invokeAfterGeneration, const MazeCallback& callback)
        {
            growingTree(width, height, invokeAfterGeneration, GrowingTreeSelectionMethod::random, callback);
        }
    }

    struct MazeParameters
    {
        std::string fileName;
        std::function<void(int, int, bool, const MazeCallback&)> function;
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

        mazeFunction(20, 20, false, [&input](int x, int y, NodeValue value)
            {
                int goldenX = 0;
                int goldenY = 0;
                int goldenValue = 0;
                input >> goldenX >> goldenY >> goldenValue;

                EXPECT_EQ(goldenX, x);
                EXPECT_EQ(goldenY, y);
                EXPECT_EQ(goldenValue, static_cast<int>(value));
            });

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
