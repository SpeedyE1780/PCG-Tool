using System.Runtime.InteropServices;

namespace PCGAPI
{
    public static class PCGEngine
    {
#if UNITY_EDITOR
        public const string DLLName = "pcg-engine-c-apid";
#else
        public const string DLLName = "pcg-engine-c-api";
#endif

        [DllImport(DLLName, EntryPoint = "setSeed")]
        public static extern void SetSeed(uint seed);
        [DllImport(DLLName, EntryPoint = "setRandomGenerator")]
        public static extern void SetRandomGenerators(SetSeed setSeed, GenerateNumber generateNumber);
        [DllImport(DLLName, EntryPoint = "setLoggingFunction")]
        public static extern void SetLoggingFunction(LogFunction logFunction);
        [DllImport(DLLName, EntryPoint = "generateMaze")]
        public static extern void GenerateMaze(int width, int height, bool invokeAfterGeneration, MazeAlgorithm algorithm, AddMazeNode addMazeNode);
        [DllImport(DLLName, EntryPoint = "simpleGeneration")]
        public static extern void SimpleGeneration(ref GenerationParameters generationParameters, Axis axis, AddNode addNode);
        [DllImport(DLLName, EntryPoint = "multiDimensionGeneration")]
        public static extern void MultiDimensionalGeneration(ref GenerationParameters generationParameters, Axis axis, bool disableOverlap, AddNode addNode);
        [DllImport(DLLName, EntryPoint = "waveFunctionCollapseGeneration")]
        public static extern void WaveFunctionCollapseGeneration(ref GenerationParameters generationParameters, ExpansionMode mode, Axis axis, AddWFCNode addNode);
        [DllImport(DLLName, EntryPoint = "waveFunctionCollapseGridGeneration")]
        public static extern void WaveFunctionCollapseGeneration(int x, int y, Axis axes, bool invokeAfterGeneration, AddWFCGridNode addNode);
        [DllImport(DLLName, EntryPoint = "waveFunctionCollapse3DGridGeneration")]
        public static extern void WaveFunctionCollapseGeneration(int x, int y, int z, bool invokeAfterGeneration, AddWFC3DGridNode addNode);
        [DllImport(DLLName, EntryPoint = "generateCombination")]
        public static extern void GenerateCombination(int elementCount, GenerateCombination generateCombination);
        [DllImport(DLLName, EntryPoint = "generateCombinationWithMinimumElementCount")]
        public static extern void GenerateCombination(int elementCount, int minimumElementCount, GenerateCombination generateCombination);
        [DllImport(DLLName, EntryPoint = "generateCombinationWithActiveElements")]
        public static extern void GenerateCombination(int elementCount, int[] includedElementsIndex, int includedElementsCount, GenerateCombination generateCombination);
        [DllImport(DLLName, EntryPoint = "generateSequence")]
        public static extern void GenerateSequence(SequenceNode sequenceNode, GetSequenceNode getNode, AddNodeToSequence addNode);
    }
}
