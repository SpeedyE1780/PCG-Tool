namespace PCGAPI.WebAPI
{
    public record GridWaveFunctionCollapseParameters2D(int Width, int Height, Axis Plane)
    {
    }

    public record GridWFCNode2D(int X, int Y, LevelGenerationDirection AdjacentNodes)
    {
    }
}
