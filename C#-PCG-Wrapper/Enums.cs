namespace PCGAPI
{
    [System.Flags]
    public enum Axis
    {
        none = 0,
        positiveX = 1 << 0,
        negativeX = 1 << 1,
        positiveY = 1 << 2,
        negativeY = 1 << 3,
        positiveZ = 1 << 4,
        negativeZ = 1 << 5,
        x = positiveX | negativeX,
        y = positiveY | negativeY,
        z = positiveZ | negativeZ,
        xy = x | y,
        xz = x | z,
        yz = y | z,
        xyz = x | y | z
    }

    public enum LevelGenerationDirection
    {
        none = 0,
        left = 1 << 0,
        right = 1 << 1,
        forward = 1 << 2,
        backward = 1 << 3,
        up = 1 << 4,
        down = 1 << 5
    }

    public enum MazeDirection
    {
        none = 0,
        left = 1 << 0,
        right = 1 << 1,
        forward = 1 << 2,
        backward = 1 << 3,
    };

    public enum ExpansionMode
    {
        BFS,
        DFS
    };

    public enum MazeAlgorithm
    {
        aldousBroder = 0,
        wilson = 1,
        binaryTreeNE = 2,
        binaryTreeNW = 3,
        binaryTreeSE = 4,
        binaryTreeSW = 5,
        sidewinder = 6,
        eller = 7,
        huntAndKill = 8,
        recursiveBacktracker = 9,
        recursiveDivision = 10,
        kruskal = 11,
        prim = 12,
        growingTreeOldest = 13,
        growingTreeMiddle = 14,
        growingTreeNewest = 15,
        growingTreeRandom = 16,
        blobbyDivisionCorridors = 17,
        blobbyDivisionSmall = 18,
        blobbyDivisionMedium = 19,
        blobbyDivisionLarge = 20,
        blobbyDivisionHuge = 21,
    }
}
