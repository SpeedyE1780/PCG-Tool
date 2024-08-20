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
    }
}
