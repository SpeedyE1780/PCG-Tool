namespace PCGAPI
{
    public delegate void AddNode(Vector3 position);
    public delegate void AddWFCNode(Vector3 position, Direction adjacentNodes);
    public delegate void AddWFCGridNode(int x, int y, Direction adjacentNodes);
    public delegate void AddWFC3DGridNode(int x, int y, int z, Direction adjacentNodes);
    public delegate void AddMazeNode(int x, int y, Direction adjacentNodes);
    public delegate void GenerateCombination(int elementIndex, bool includedInSet);
    public delegate void SetSeed(uint seed);
    public delegate int GenerateNumber(int min, int max);
    public delegate void LogFunction(string message);
    public delegate SequenceNode GetSequenceNode(int index);
    public delegate void AddNodeToSequence(int index);
}
