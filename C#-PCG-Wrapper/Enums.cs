namespace PCGAPI
{
    /// <summary>
    /// Axis used to generate levels
    /// </summary>
    [System.Flags]
    public enum Axis
    {
        /// <summary>
        /// No axis used
        /// </summary>
        none = 0,
        /// <summary>
        /// +X Axis
        /// </summary>
        positiveX = 1 << 0,
        /// <summary>
        /// -X Axis
        /// </summary>
        negativeX = 1 << 1,
        /// <summary>
        /// +Y Axis
        /// </summary>
        positiveY = 1 << 2,
        /// <summary>
        /// -Y Axis
        /// </summary>
        negativeY = 1 << 3,
        /// <summary>
        /// +Z Axis
        /// </summary>
        positiveZ = 1 << 4,
        /// <summary>
        /// -Z Axis
        /// </summary>
        negativeZ = 1 << 5,
        /// <summary>
        /// X Axis
        /// </summary>
        x = positiveX | negativeX,
        /// <summary>
        /// Y Axis
        /// </summary>
        y = positiveY | negativeY,
        /// <summary>
        /// Z Axis
        /// </summary>
        z = positiveZ | negativeZ,
        /// <summary>
        /// XY Plane
        /// </summary>
        xy = x | y,
        /// <summary>
        /// XZ Plane
        /// </summary>
        xz = x | z,
        /// <summary>
        /// YZ Plane
        /// </summary>
        yz = y | z,
        /// <summary>
        /// XYZ Plane
        /// </summary>
        xyz = x | y | z
    }

    /// <summary>
    /// Plane used in level generation
    /// </summary>
    public enum Plane
    {
        /// <summary>
        /// XY Plane
        /// </summary>
        xy = Axis.xy,
        /// <summary>
        /// XZ Plane
        /// </summary>
        xz = Axis.xz,
        /// <summary>
        /// YZ Plane
        /// </summary>
        yz = Axis.yz,
    }

    /// <summary>
    /// Indicates adjacent nodes for generated nodes in levels
    /// </summary>
    public enum LevelGenerationDirection
    {
        /// <summary>
        /// No adjacent nodes
        /// </summary>
        none = 0,
        /// <summary>
        /// Left adjacent node
        /// </summary>
        left = 1 << 0,
        /// <summary>
        /// Right adjacent node
        /// </summary>
        right = 1 << 1,
        /// <summary>
        /// Forward adjacent node
        /// </summary>
        forward = 1 << 2,
        /// <summary>
        /// Backward adjacent node
        /// </summary>
        backward = 1 << 3,
        /// <summary>
        /// Up adjacent node
        /// </summary>
        up = 1 << 4,
        /// <summary>
        /// Down adjacent node
        /// </summary>
        down = 1 << 5
    }

    /// <summary>
    /// Indicates adjacent nodes for generated nodes in mazes
    /// </summary>
    public enum MazeDirection
    {
        /// <summary>
        /// No adjacent nodes
        /// </summary>
        none = 0,
        /// <summary>
        /// Left adjacent node
        /// </summary>
        left = 1 << 0,
        /// <summary>
        /// Right adjacent node
        /// </summary>
        right = 1 << 1,
        /// <summary>
        /// Forward adjacent node
        /// </summary>
        forward = 1 << 2,
        /// <summary>
        /// Backward adjacent node
        /// </summary>
        backward = 1 << 3,
    };

    /// <summary>
    /// Indicates whether to use a Breadth-First or Depth-First approach with Wave Function Collapse Generation
    /// </summary>
    public enum ExpansionMode
    {
        /// <summary>
        /// Breadth-First Search
        /// </summary>
        BFS,
        /// <summary>
        /// Depth-First Search
        /// </summary>
        DFS
    };

    /// <summary>
    /// Algorithm used to generate maze
    /// </summary>
    public enum MazeAlgorithm
    {
        /// <summary>
        /// Aldous Broder
        /// </summary>
        aldousBroder = 0,
        /// <summary>
        /// Wilson
        /// </summary>
        wilson = 1,
        /// <summary>
        /// Binary Tree with a corrider along the North and East
        /// </summary>
        binaryTreeNE = 2,
        /// <summary>
        /// Binary Tree with a corrider along the North and West
        /// </summary>
        binaryTreeNW = 3,
        /// <summary>
        /// Binary Tree with a corrider along the South and East
        /// </summary>
        binaryTreeSE = 4,
        /// <summary>
        /// Binary Tree with a corrider along the South and West
        /// </summary>
        binaryTreeSW = 5,
        /// <summary>
        /// Sidewinder
        /// </summary>
        sidewinder = 6,
        /// <summary>
        /// Eller
        /// </summary>
        eller = 7,
        /// <summary>
        /// Hunt And Kill
        /// </summary>
        huntAndKill = 8,
        /// <summary>
        /// Recursive Backtracker
        /// </summary>
        recursiveBacktracker = 9,
        /// <summary>
        /// Recursive Division
        /// </summary>
        recursiveDivision = 10,
        /// <summary>
        /// Kruskal
        /// </summary>
        kruskal = 11,
        /// <summary>
        /// Prim
        /// </summary>
        prim = 12,
        /// <summary>
        /// Growing Tree select: Oldest Node
        /// </summary>
        growingTreeOldest = 13,
        /// <summary>
        /// Growing Tree select: Middle Node
        /// </summary>
        growingTreeMiddle = 14,
        /// <summary>
        /// Growing Tree select: Newest Node
        /// </summary>
        growingTreeNewest = 15,
        /// <summary>
        /// Growing Tree select: Random Node
        /// </summary>
        growingTreeRandom = 16,
        /// <summary>
        /// Blobby Division with no regions
        /// </summary>
        blobbyDivisionCorridors = 17,
        /// <summary>
        /// Blobby Division with small regions
        /// </summary>
        blobbyDivisionSmall = 18,
        /// <summary>
        /// Blobby Division with meduim regions
        /// </summary>
        blobbyDivisionMedium = 19,
        /// <summary>
        /// Blobby Division with large regions
        /// </summary>
        blobbyDivisionLarge = 20,
        /// <summary>
        /// Blobby Division with huge regions
        /// </summary>
        blobbyDivisionHuge = 21,
    }
}
