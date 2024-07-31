using System.Runtime.InteropServices;

namespace PCGAPI
{
#pragma warning disable CA1401 // P/Invokes should not be visible
    public static partial class PCGEngine
    {
        public const string DLLName = "pcg-engine-c-api";

        [LibraryImport(DLLName, EntryPoint = "setSeed")]
        public static partial void SetSeed(uint seed);
        [LibraryImport(DLLName, EntryPoint = "setRandomGenerator")]
        public static partial void SetRandomGenerators(SetSeed setSeed, GenerateNumber generateNumber);
        [LibraryImport(DLLName, EntryPoint = "setLoggingFunction")]
        public static partial void SetLoggingFunction(LogFunction logFunction);
        [LibraryImport(DLLName, EntryPoint = "generateMaze")]
        public static partial void GenerateMaze(int width, int height, [MarshalAs(UnmanagedType.Bool)] bool invokeAfterGeneration, MazeAlgorithm algorithm, AddMazeNode addMazeNode);
        [LibraryImport(DLLName, EntryPoint = "simpleGeneration")]
        public static partial void SimpleGeneration(ref GenerationParameters generationParameters, Axis axis, AddNode addNode);
        [LibraryImport(DLLName, EntryPoint = "multiDimensionGeneration")]
        public static partial void MultiDimensionalGeneration(ref GenerationParameters generationParameters, Axis axis, [MarshalAs(UnmanagedType.Bool)] bool disableOverlap, AddNode addNode);
        [LibraryImport(DLLName, EntryPoint = "waveFunctionCollapseGeneration")]
        public static partial void WaveFunctionCollapseGeneration(ref GenerationParameters generationParameters, ExpansionMode mode, Axis axis, AddWFCNode addNode);
        [LibraryImport(DLLName, EntryPoint = "waveFunctionCollapseGridGeneration")]
        public static partial void WaveFunctionCollapseGeneration(int x, int y, Axis axes, [MarshalAs(UnmanagedType.Bool)] bool invokeAfterGeneration, AddWFCGridNode addNode);
        [LibraryImport(DLLName, EntryPoint = "waveFunctionCollapse3DGridGeneration")]
        public static partial void WaveFunctionCollapseGeneration(int x, int y, int z, [MarshalAs(UnmanagedType.Bool)] bool invokeAfterGeneration, AddWFC3DGridNode addNode);
        [LibraryImport(DLLName, EntryPoint = "generateCombination")]
        public static partial void GenerateCombination(int elementCount, GenerateCombination generateCombination);
        [LibraryImport(DLLName, EntryPoint = "generateCombinationWithMinimumElementCount")]
        public static partial void GenerateCombination(int elementCount, int minimumElementCount, GenerateCombination generateCombination);
        [LibraryImport(DLLName, EntryPoint = "generateCombinationWithActiveElements")]
        public static partial void GenerateCombination(int elementCount, in int[] includedElementsIndex, int includedElementsCount, GenerateCombination generateCombination);
        [LibraryImport(DLLName, EntryPoint = "generateSequence")]
        public static partial void GenerateSequence(int nextNodes, UpdateSequence updateSequence);
    }
#pragma warning restore CA1401 // P/Invokes should not be visible
}
