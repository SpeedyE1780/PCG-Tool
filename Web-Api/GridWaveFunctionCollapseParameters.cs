﻿namespace PCGAPI.WebAPI
{
    public record GridWaveFunctionCollapseParameters2D(int Width, int Height, Plane Plane)
    {
    }

    public record GridWFCNode2D(int X, int Y, LevelGenerationDirection AdjacentNodes)
    {
    }

    public record GridWaveFunctionCollapseParameters3D(int Width, int Height, int Depth)
    {
    }

    public record GridWFCNode3D(int X, int Y, int Z, LevelGenerationDirection AdjacentNodes)
    {
    }
}
