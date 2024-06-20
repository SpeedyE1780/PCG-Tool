using System.Runtime.InteropServices;

namespace PCGAPI
{
    public static class PCGEngine
    {
        [DllImport("pcg-engine-c-apid", EntryPoint = "setSeed")]
        public static extern void SetSeed(uint seed);
        [DllImport("pcg-engine-c-apid", EntryPoint = "setLoggingFunction")]
        public static extern void SetLoggingFunction(LogFunction logFunction);
        [DllImport("pcg-engine-c-apid", EntryPoint = "generateMaze")]
        public static extern void GenerateMaze(int width, int height, bool invokeAfterGeneration, MazeAlgorithm algorithm, AddMazeNode addMazeNode);
    }
}
