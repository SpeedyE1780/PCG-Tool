using System.Runtime.InteropServices;

namespace PCGAPI
{
    public static class PCGEngine
    {
        [DllImport("PCG-Engine-C-API", EntryPoint = "simpleGeneration")]
        public static extern void SimpleGenerator(ref GenerationParameters data, Axis axis, AddNode addNode);
        [DllImport("PCG-Engine-C-API", EntryPoint = "multiDimensionGeneration")]
        public static extern void MultiDimensionGenerator(ref GenerationParameters data, Axis axis, bool disableOverlap, AddNode addNode);
        [DllImport("PCG-Engine-C-API", EntryPoint = "setSeed")]
        public static extern void UpdateSeed(uint seed);
        [DllImport("PCG-Engine-C-API", EntryPoint = "setRandomGenerator")]
        public static extern void SetRandomGenerators(SetSeed setSeed, GenerateNumber generate);
        [DllImport("PCG-Engine-C-API", EntryPoint = "setLoggingFunction")]
        public static extern void SetLoggingFunction(LogFunction logFunction);
        [DllImport("PCG-Engine-C-API", EntryPoint = "waveFunctionCollapseGeneration")]
        public static extern void WaveFunctionCollapse(ref GenerationParameters data, ExpansionMode mode, Axis axis, AddWFCNode addWFCNode);
        [DllImport("PCG-Engine-C-API", EntryPoint = "generateMaze")]
        public static extern void GenerateMaze(int width, int height, MazeAlgorithm algorithm, AddMazeNode addMazeNode);
    }
}
