namespace PCGAPI.Tests.LevelGeneration
{
    public class WaveFunctionCollapse : PCGTest
    {
        static GenerationParameters Parameters => new()
        {
            count = 200,
            size = 1
        };

        private static void WaveFunctionCollapseTest(ExpansionMode mode, string filePath)
        {
            var levelNodes = File.ReadAllLines(filePath);
            int index = 0;

            PCGEngine.WaveFunctionCollapseGeneration(Parameters, mode, Axis.xyz, (position, adjacent) =>
            {
                string expectedLevelNode = levelNodes[index];
                index++;
                Assert.Equal(expectedLevelNode, $"{position.x} {position.y} {position.z} {(int)adjacent}");
            });
        }

        private static void WaveFunctionCollapse4DTest(ExpansionMode mode, string filePath)
        {
            var levelNodes = File.ReadAllLines(filePath);
            int index = 0;

            PCGEngine.WaveFunctionCollapse4DGeneration(Parameters, mode, Axis.xyz, (position, adjacent) =>
            {
                string expectedLevelNode = levelNodes[index];
                index++;
                Assert.Equal(expectedLevelNode, $"{position.x} {position.y} {position.z} {position.w} {(int)adjacent}");
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
        public void BFS4D()
        {
            string filePath = "GoldenValues/WaveFunctionCollapse/4DBFS.txt";
            WaveFunctionCollapse4DTest(ExpansionMode.BFS, filePath);
        }

        [Fact]
        public void DFS4D()
        {
            string filePath = "GoldenValues/WaveFunctionCollapse/4DDFS.txt";
            WaveFunctionCollapse4DTest(ExpansionMode.DFS, filePath);
        }
    }
}
