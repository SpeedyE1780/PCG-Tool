using System.Runtime.InteropServices;

namespace PCGAPI
{
    public static class PCGEngine
    {
        [DllImport("pcg-engine-c-apid", EntryPoint = "generateMaze")]
        public static extern void GenerateMaze(int width, int height, bool invokeAfterGeneration, MazeAlgorithm algorithm, AddMazeNode addMazeNode);
    }
}
