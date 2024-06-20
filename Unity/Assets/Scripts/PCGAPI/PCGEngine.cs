using System.Runtime.InteropServices;

namespace PCGAPI
{
    public static class PCGEngine
    {
        [DllImport("pcg-engine-c-apid", EntryPoint = "setSeed")]
        public static extern void SetSeed(uint seed);
        [DllImport("pcg-engine-c-apid", EntryPoint = "setRandomGenerator")]
        public static extern void SetRandomGenerators(SetSeed setSeed, GenerateNumber generateNumber);
        [DllImport("pcg-engine-c-apid", EntryPoint = "setLoggingFunction")]
        public static extern void SetLoggingFunction(LogFunction logFunction);
        [DllImport("pcg-engine-c-apid", EntryPoint = "generateMaze")]
        public static extern void GenerateMaze(int width, int height, bool invokeAfterGeneration, MazeAlgorithm algorithm, AddMazeNode addMazeNode);
        [DllImport("pcg-engine-c-apid", EntryPoint = "simpleGeneration")]
        public static extern void SimpleGeneration(ref GenerationParameters generationParameters, Axis axis, AddNode addNode);
        [DllImport("pcg-engine-c-apid", EntryPoint = "multiDimensionGeneration")]
        public static extern void MultiDimensionalGeneration(ref GenerationParameters generationParameters, Axis axis, bool disableOverlap, AddNode addNode);
        [DllImport("pcg-engine-c-apid", EntryPoint = "waveFunctionCollapseGeneration")]
        public static extern void WaveFunctionCollapseGeneration(ref GenerationParameters generationParameters, ExpansionMode mode, Axis axis, AddWFCNode addNode);
        [DllImport("pcg-engine-c-apid", EntryPoint = "generateCombination")]
        public static extern void GenerateCombination(int elementCount, GenerateCombination generateCombination);
        [DllImport("pcg-engine-c-apid", EntryPoint = "generateCombinationWithMinimumElementCount")]
        public static extern void GenerateCombination(int elementCount, int minimumElementCount, GenerateCombination generateCombination);
        [DllImport("pcg-engine-c-apid", EntryPoint = "generateCombinationWithActiveElements")]
        public static extern void GenerateCombination(int elementCount, int[] includedElementsIndex, int includedElementsCount, GenerateCombination generateCombination);
    }
}
