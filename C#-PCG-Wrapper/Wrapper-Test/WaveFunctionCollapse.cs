namespace PCGAPI.Tests.LevelGeneration
{
    public class WaveFunctionCollapse : PCGTest
    {
        private static void WaveFunctionCollapseTest(ExpansionMode mode, string filePath)
        {
            var positions = File.ReadAllLines(filePath);
            int index = 0;

            GenerationParameters parameters = new()
            {
                count = 200,
                size = 1
            };

            PCGEngine.WaveFunctionCollapseGeneration(ref parameters, mode, Axis.xyz, (position, adjacent) =>
            {
                (Vector3 expectedPosition, LevelGenerationDirection expectedAdjacent) = ConvertLineToWFCData(positions[index]);
                index++;
                Assert.Equal(expectedPosition, position);
                Assert.Equal(expectedAdjacent, adjacent);
            });
        }

        [Fact]
        public void BFS()
        {
            string filePath = "GoldenValues/WaveFunctionCollapse/BFS.txt";
            WaveFunctionCollapseTest(ExpansionMode.BFS, filePath);
        }

        [Fact]
        public void DFS()
        {
            string filePath = "GoldenValues/WaveFunctionCollapse/DFS.txt";
            WaveFunctionCollapseTest(ExpansionMode.DFS, filePath);
        }

        [Fact]
        public void Grid2D()
        {
            string filePath = "GoldenValues/WaveFunctionCollapse/Grid2D.txt";
            var positions = File.ReadAllLines(filePath);
            int index = 0;

            PCGEngine.WaveFunctionCollapseGeneration(10, 10, Axis.xz, false, (x, y, adjacentNode) =>
            {
                (int expectedX, int expectedY, LevelGenerationDirection expectedAdjacent) = ConvertLineToWFC2DData(positions[index]);
                index++;

                Assert.Equal(expectedX, x);
                Assert.Equal(expectedY, y);
                Assert.Equal(expectedAdjacent, adjacentNode);
            });
        }

        [Fact]
        public void Grid3D()
        {
            string filePath = "GoldenValues/WaveFunctionCollapse/Grid3D.txt";
            var positions = File.ReadAllLines(filePath);
            int index = 0;

            PCGEngine.WaveFunctionCollapseGeneration(10, 10, 10, false, (x, y, z, adjacentNode) =>
            {
                (int expectedX, int expectedY, int expectedZ, LevelGenerationDirection expectedAdjacent) = ConvertLineToWFC3DData(positions[index]);
                index++;

                Assert.Equal(expectedX, x);
                Assert.Equal(expectedY, y);
                Assert.Equal(expectedZ, z);
                Assert.Equal(expectedAdjacent, adjacentNode);
            });
        }
    }
}
