using System.Runtime.InteropServices;

namespace PCGAPI
{
    /// <summary>
    /// PCGEngine is the middleman between the C# code and native C++ code
    /// </summary>
    public static class PCGEngine
    {
        /// <summary>
        /// Name of DLL
        /// </summary>
        public const string DLLName = "pcg-engine-c-api";

        /// <summary>
        /// Set the RNG Seed
        /// </summary>
        /// <param name="seed">New seed value</param>
        [DllImport(DLLName, EntryPoint = "setSeed")]
        public static extern void SetSeed(uint seed);
        /// <summary>
        /// Set RNG generators
        /// </summary>
        /// <param name="setSeed">Function that will update the seed</param>
        /// <param name="generateNumber">Function that will generate numbers</param>
        [DllImport(DLLName, EntryPoint = "setRandomGenerator")]
        public static extern void SetRandomGenerators(SetSeed setSeed, GenerateNumber generateNumber);
        /// <summary>
        /// Set function to log C++ message
        /// </summary>
        /// <param name="logFunction">Function that will log messages</param>
        [DllImport(DLLName, EntryPoint = "setLoggingFunction")]
        public static extern void SetLoggingFunction(LogFunction logFunction);
        /// <summary>
        /// Generate a maze using the passed in algorithm
        /// </summary>
        /// <param name="width">Grid Width</param>
        /// <param name="height">Grid Height</param>
        /// <param name="invokeAfterGeneration">If true callback will only be called after all nodes are generated</param>
        /// <param name="algorithm">Algorithm that will be used to generate maze</param>
        /// <param name="addMazeNode">Callback when a node is generated</param>
        [DllImport(DLLName, EntryPoint = "generateMaze")]
        public static extern void GenerateMaze(int width, int height, [MarshalAs(UnmanagedType.Bool)] bool invokeAfterGeneration, MazeAlgorithm algorithm, AddMazeNode addMazeNode);
        /// <summary>
        /// Generate a Growing Tree maze using a custom selection callback
        /// </summary>
        /// <param name="width">Grid width</param>
        /// <param name="height">Grid height</param>
        /// <param name="invokeAfterGeneration">If true callback will only be called after all nodes are generated</param>
        /// <param name="nodeCallback">Callback used to select a node from pending growing tree nodes</param>
        /// <param name="addMazeNode">Callback when a node is generated</param>
        [DllImport(DLLName, EntryPoint = "generateGrowingTreeWithCustomSelection")]
        public static extern void GenerateGrowingTreeMaze(int width, int height, [MarshalAs(UnmanagedType.Bool)] bool invokeAfterGeneration, SelectNode nodeCallback, AddMazeNode addMazeNode);
        /// <summary>
        /// Geneate maze using Blobby Division Algorithm
        /// </summary>
        /// <param name="width">Grid Width</param>
        /// <param name="height">Grid Height</param>
        /// <param name="invokeAfterGeneration">If true callback will only be called after all nodes are generated</param>
        /// <param name="regionThreshold">User defined region threshold</param>
        /// <param name="callback">Callback when a node is generated</param>
        [DllImport(DLLName, EntryPoint = "generateBlobbyDivisionWithCustomRegionThreshold")]
        public static extern void GenerateBlobbyDivisionMaze(int width, int height, bool invokeAfterGeneration, int regionThreshold, AddMazeNode callback);
        /// <summary>
        /// Generate a linear level on a single axis
        /// </summary>
        /// <param name="generationParameters">Object containing number of nodes that need to be generated, node size and starting position</param>
        /// <param name="offset">Offset between nodes</param>
        /// <param name="addNode">Callback when a node is generated</param>
        [DllImport(DLLName, EntryPoint = "simpleGeneration")]
        public static extern void SimpleGeneration(GenerationParameters generationParameters, Vector3 offset, AddNode addNode);
        /// <summary>
        /// Generate a level on multiple axes
        /// </summary>
        /// <param name="generationParameters">Object containing number of nodes that need to be generated, node size and starting position</param>
        /// <param name="axis">Axes flag indicating which axes are being used</param>
        /// <param name="disableOverlap">If true nodes cannot be generated on top of one another</param>
        /// <param name="addNode">Callback when a node is generated</param>
        [DllImport(DLLName, EntryPoint = "multiDimensionGeneration")]
        public static extern void MultiDimensionalGeneration(GenerationParameters generationParameters, Axis axis, [MarshalAs(UnmanagedType.Bool)] bool disableOverlap, AddNode addNode);
        /// <summary>
        /// Generate a level using the Wave Function Collapse Algorithm
        /// </summary>
        /// <param name="generationParameters">Object containing number of nodes that need to be generated, node size and starting position</param>
        /// <param name="mode">If Breadth-First Search (BFS) or Depth-First Search (DFS) expansion should be used</param>
        /// <param name="axis">Axes flag indicating which axes are being used</param>
        /// <param name="addNode">Callback when a node is generated</param>
        [DllImport(DLLName, EntryPoint = "waveFunctionCollapseGeneration")]
        public static extern void WaveFunctionCollapseGeneration(GenerationParameters generationParameters, ExpansionMode mode, Axis axis, AddWFCNode addNode);
        /// <summary>
        /// Generate a 4D level using the Wave Function Collapse Algorithm
        /// </summary>
        /// <param name="generationParameters">Object containing number of nodes that need to be generated, node size and starting position</param>
        /// <param name="mode">If Breadth-First Search (BFS) or Depth-First Search (DFS) expansion should be used</param>
        /// <param name="axis">Axes flag indicating which axes are being used</param>
        /// <param name="addNode">Callback when a node is generated</param>
        [DllImport(DLLName, EntryPoint = "waveFunctionCollapse4DGeneration")]
        public static extern void WaveFunctionCollapse4DGeneration(GenerationParameters generationParameters, ExpansionMode mode, Axis axis, AddWFC4DNode addNode);
        /// <summary>
        ///  Generate a grid using the Wave Function Collapse Algorithm
        /// </summary>
        /// <param name="x">Grid width</param>
        /// <param name="y">Grid height</param>
        /// <param name="plane">Plane indicating on which plane is the grid being spawned</param>
        /// <param name="invokeAfterGeneration">If true callback will only be called after all nodes are generated</param>
        /// <param name="addNode">Callback when a node is generated</param>
        [DllImport(DLLName, EntryPoint = "waveFunctionCollapseGridGeneration")]
        public static extern void WaveFunctionCollapseGeneration(int x, int y, Plane plane, [MarshalAs(UnmanagedType.Bool)] bool invokeAfterGeneration, AddWFCGridNode addNode);
        /// <summary>
        /// Generate a grid using the Wave Function Collapse Algorithm
        /// </summary>
        /// <param name="x">Grid width</param>
        /// <param name="y">Grid height</param>
        /// <param name="z">Grid depth</param>
        /// <param name="invokeAfterGeneration">If true callback will only be called after all nodes are generated</param>
        /// <param name="addNode">Callback when a node is generated</param>
        [DllImport(DLLName, EntryPoint = "waveFunctionCollapse3DGridGeneration")]
        public static extern void WaveFunctionCollapseGeneration(int x, int y, int z, [MarshalAs(UnmanagedType.Bool)] bool invokeAfterGeneration, AddWFC3DGridNode addNode);
        /// <summary>
        /// Generate a combination given a number of elements
        /// </summary>
        /// <param name="elementCount">Number of element that are available in set</param>
        /// <param name="generateCombination">Callback to add element to generated set</param>
        [DllImport(DLLName, EntryPoint = "generateCombination")]
        public static extern void GenerateCombination(int elementCount, GenerateCombination generateCombination);
        /// <summary>
        /// Generate a combination with at least minimumElementCount elements
        /// </summary>
        /// <param name="elementCount">Number of element that are available in set</param>
        /// <param name="minimumElementCount">Minimum number of elements in set</param>
        /// <param name="generateCombination">Callback to add element to generated set</param>
        [DllImport(DLLName, EntryPoint = "generateCombinationWithMinimumElementCount")]
        public static extern void GenerateCombination(int elementCount, int minimumElementCount, GenerateCombination generateCombination);
        /// <summary>
        /// Generate a combination with the given elements active
        /// </summary>
        /// <param name="elementCount">Number of element that are available in set</param>
        /// <param name="includedElementsIndex">Array of elements that must be included</param>
        /// <param name="includedElementsCount">Number of elements in activeElementsIndex array</param>
        /// <param name="generateCombination">Callback to add element to generated set</param>
        [DllImport(DLLName, EntryPoint = "generateCombinationWithActiveElements")]
        public static extern void GenerateCombination(int elementCount, int[] includedElementsIndex, int includedElementsCount, GenerateCombination generateCombination);
        /// <summary>
        /// Generate a sequence starting from node
        /// </summary>
        /// <param name="nextNodes">Count of next nodes from first node in sequence</param>
        /// <param name="updateSequence">Callback to add next node in sequence and returns next node possibility count</param>
        [DllImport(DLLName, EntryPoint = "generateSequence")]
        private static extern void GenerateSequence(int nextNodes, UpdateSequence updateSequence);

        /// <summary>
        /// Generate a sequence starting from node
        /// </summary>
        /// <param name="node">First node in sequence</param>
        /// <param name="updateSequence">Callback to add next node in sequence and returns next node possibility count</param>
        public static void GenerateSequence(ISequenceNode node, UpdateSequence updateSequence)
        {
            GenerateSequence(node.NextCount, updateSequence);
        }

        /// <summary>
        /// Generate a sequence that can contain cycles starting with node
        /// </summary>
        /// <param name="nextNodeCount">Count of next nodes from first node in sequence</param>
        /// <param name="sequenceLength">Max length of generated sequence</param>
        /// <param name="updateSequence">Callback to add next node in sequence and returns next node possibility count</param>
        [DllImport(DLLName, EntryPoint = "generateCyclicSequence")]
        private static extern void GenerateCyclicSequence(int nextNodeCount, int sequenceLength, UpdateSequence updateSequence);
        /// <summary>
        /// Generate a sequence that can contain cycles starting with node
        /// </summary>
        /// <param name="node">First node in sequence</param>
        /// <param name="sequenceLength">Max length of generated sequence</param>
        /// <param name="updateSequence">Callback to add next node in sequence and returns next node possibility count</param>
        public static void GenerateCyclicSequence(ISequenceNode node, int sequenceLength, UpdateSequence updateSequence)
        {
            GenerateCyclicSequence(node.NextCount, sequenceLength, updateSequence);
        }
    }
}
