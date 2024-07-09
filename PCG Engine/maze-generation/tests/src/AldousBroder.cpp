#include <pcg/engine/maze-generation/AldousBroder.hpp>
#include <pcg/engine/maze-generation/BinaryTree.hpp>
#include <pcg/engine/maze-generation/Eller.hpp>
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
    }

    struct MazeParameters
    {
        std::string fileName;
        std::function<void(int, int, bool, MazeCallback&&)> function;
    };

    class MazeAlgorithmTest : public ::testing::TestWithParam<MazeParameters> { };

    TEST_P(MazeAlgorithmTest, Maze)
    {
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
            MazeParameters{ "Eller", eller },
            MazeParameters{ "HuntAndKill", huntAndKill },
            MazeParameters{ "Kruskal", kruskal },
            MazeParameters{ "Prim", prim },
            MazeParameters{ "RecursiveBacktracker", recursiveBacktracker },
            MazeParameters{ "RecursiveDivision", recursiveDivision },
            MazeParameters{ "Sidewinder", sidewinder },
            MazeParameters{ "Wilson", wilson }
        ));
}
