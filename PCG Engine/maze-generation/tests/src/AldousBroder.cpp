#include <pcg/engine/maze-generation/AldousBroder.hpp>

#include <gtest/gtest.h>

#include <functional>
#include <fstream>

namespace pcg::engine::maze_generation::tests
{
	TEST(MazeGeneration, AldousBroder)
	{
		std::ifstream input("GoldenValues/AldousBroder.txt");

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

		aldousBroder(20, 20, false, callback);

		input.close();
	}
}
