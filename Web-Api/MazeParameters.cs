namespace PCGAPI.WebAPI
{
    public record MazeParameters(int Width, int Height, MazeAlgorithm Algorithm)
    {
    }

    public record MazeNode(int X, int Y, MazeDirection AdjacentNodes)
    {
    }
}
