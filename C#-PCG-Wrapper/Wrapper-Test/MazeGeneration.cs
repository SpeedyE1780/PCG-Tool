﻿using System.Collections;

namespace PCGAPI.Tests.MazeGeneration
{
    public class MazeGeneration : PCGTest
    {
        class MazeData : IEnumerable<object[]>
        {
            public IEnumerator<object[]> GetEnumerator()
            {
                foreach (MazeAlgorithm algorithm in Enum.GetValues(typeof(MazeAlgorithm)))
                {
                    string fileName = algorithm.ToString();
                    string filePath = "GoldenValues/" + char.ToUpper(fileName[0]) + fileName[1..] + ".txt";
                    yield return new object[] { algorithm, filePath };
                }
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }
        }

        [Theory]
        [ClassData(typeof(MazeData))]
        public void Maze(MazeAlgorithm mazeAlgorithm, string filePath)
        {
            var data = File.ReadAllLines(filePath);
            int index = 0;

            PCGEngine.GenerateMaze(20, 20, false, mazeAlgorithm, (x, y, adjacent) =>
            {
                (int expectedX, int expectedY, MazeDirection expectedAdjacent) = ConvertLineToMazeData(data[index]);
                index++;

                Assert.Equal(expectedX, x);
                Assert.Equal(expectedY, y);
                Assert.Equal(expectedAdjacent, adjacent);
            });
        }
    }
}
