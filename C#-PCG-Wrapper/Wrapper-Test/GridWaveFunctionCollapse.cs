using System.Collections;

namespace PCGAPI.Tests.LevelGeneration
{
    public class GridWaveFunctionCollapse : PCGTest
    {
        class Grid2DParams : IEnumerable<object[]>
        {
            public IEnumerator<object[]> GetEnumerator()
            {
                yield return new object[] { Plane.xy, "GoldenValues/WaveFunctionCollapse/Grid2DXY.txt" };
                yield return new object[] { Plane.xz, "GoldenValues/WaveFunctionCollapse/Grid2DXZ.txt" };
                yield return new object[] { Plane.yz, "GoldenValues/WaveFunctionCollapse/Grid2DYZ.txt" };
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }
        }

        [Theory]
        [ClassData(typeof(Grid2DParams))]
        public void Grid2D(Plane plane, string filePath)
        {
            var gridNodes = File.ReadAllLines(filePath);
            int index = 0;

            PCGEngine.WaveFunctionCollapseGeneration(10, 10, plane, false, (x, y, adjacentNode) =>
            {
                string expectedWfcNode = gridNodes[index];
                index++;
                Assert.Equal(expectedWfcNode, $"{x} {y} {(int)adjacentNode}");
            });
        }

        [Fact]
        public void Grid3D()
        {
            string filePath = "GoldenValues/WaveFunctionCollapse/Grid3D.txt";
            var gridNodes = File.ReadAllLines(filePath);
            int index = 0;

            PCGEngine.WaveFunctionCollapseGeneration(10, 10, 10, false, (x, y, z, adjacentNode) =>
            {
                string expectedWfcNode = gridNodes[index];
                index++;
                Assert.Equal(expectedWfcNode, $"{x} {y} {z} {(int)adjacentNode}");
            });
        }
    }
}
