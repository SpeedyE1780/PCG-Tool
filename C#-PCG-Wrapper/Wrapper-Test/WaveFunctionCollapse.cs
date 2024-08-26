namespace PCGAPI.Tests.LevelGeneration
{
    public class WaveFunctionCollapse : PCGTest
    {
        private static void WaveFunctionCollapseTest(ExpansionMode mode, string filePath)
        {
            var levelNodes = File.ReadAllLines(filePath);
            int index = 0;

            GenerationParameters parameters = new()
            {
                count = 200,
                size = 1
            };

            PCGEngine.WaveFunctionCollapseGeneration(parameters, mode, Axis.xyz, (position, adjacent) =>
            {
                string expectedLevelNode = levelNodes[index];
                index++;
                Assert.Equal(expectedLevelNode, $"{position.x} {position.y} {position.z} {(int)adjacent}");
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
    }
}
