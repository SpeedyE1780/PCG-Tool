namespace PCGAPI
{
    /// <summary>
    /// Notifies that a node was a spawned at position
    /// </summary>
    /// <param name="position">Spawned node position</param>
    public delegate void AddNode(Vector3 position);
    /// <summary>
    /// Notifies that a node was a spawned at position and has the following adjacent nodes
    /// </summary>
    /// <param name="position">Spawned node position</param>
    /// <param name="adjacentNodes">Spawned node adjacent nodes</param>
    public delegate void AddWFCNode(Vector3 position, LevelGenerationDirection adjacentNodes);
    /// <summary>
    /// Notifies that a node was a spawned at position and has the following adjacent nodes
    /// </summary>
    /// <param name="position">Spawned node position</param>
    /// <param name="adjacentNodes">Spawned node adjacent nodes</param>
    public delegate void AddWFC4DNode(Vector4 position, LevelGenerationDirection adjacentNodes);
    /// <summary>
    /// Notifies that a node was a spawned at (x, y) coordinates and has the following adjacent nodes
    /// </summary>
    /// <param name="x">X coordinate</param>
    /// <param name="y">Y coordinate</param>
    /// <param name="adjacentNodes">Spawned node adjacent nodes</param>
    public delegate void AddWFCGridNode(int x, int y, LevelGenerationDirection adjacentNodes);
    /// <summary>
    /// Notifies that a node was a spawned at (x, y, z) coordinates and has the following adjacent nodes
    /// </summary>
    /// <param name="x">X coordinate</param>
    /// <param name="y">Y coordinate</param>
    /// <param name="z">Z coordinate</param>
    /// <param name="adjacentNodes">Spawned node adjacent nodes</param>
    public delegate void AddWFC3DGridNode(int x, int y, int z, LevelGenerationDirection adjacentNodes);
    /// <summary>
    /// Notifies that a node was a spawned at (x, y) coordinates and has the following adjacent nodes
    /// </summary>
    /// <param name="x">X coordinate</param>
    /// <param name="y">Y coordinate</param>
    /// <param name="adjacentNodes">Spawned node adjacent nodes</param>
    public delegate void AddMazeNode(int x, int y, MazeDirection adjacentNodes);
    /// <summary>
    /// User defined function to select next node in growing tree maze
    /// </summary>
    /// <param name="count">Next nodes count</param>
    /// <returns>Next node index</returns>
    public delegate int SelectNode(int count);
    /// <summary>
    /// Notifies if element at index is included in combination or not
    /// </summary>
    /// <param name="elementIndex">Index of element in combination</param>
    /// <param name="includedInSet">True if is included in combination</param>
    public delegate void GenerateCombination(int elementIndex, bool includedInSet);
    /// <summary>
    /// Sets the RNG seed
    /// </summary>
    /// <param name="seed">New seed value</param>
    public delegate void SetSeed(uint seed);
    /// <summary>
    /// Generates a number in range [min, max[
    /// </summary>
    /// <param name="min">Minimum value generated</param>
    /// <param name="max">Maximum value generated</param>
    /// <returns>Number in range [min, max[</returns>
    public delegate int GenerateNumber(int min, int max);
    /// <summary>
    /// Logs message from native DLL
    /// </summary>
    /// <param name="message">Message logged</param>
    public delegate void LogFunction(string message);
    /// <summary>
    /// Update node in sequence and notifies which node is next (-1 if current node is the last)
    /// </summary>
    /// <param name="index">index of next nodes</param>
    /// <returns>Number of possible next nodes</returns>
    public delegate int UpdateSequence(int index);
}
