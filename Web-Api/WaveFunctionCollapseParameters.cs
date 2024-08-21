﻿namespace PCGAPI.WebAPI
{
    public record WaveFunctionCollapseParameters(uint NodeCount, float NodeSize, Vector3 StartPosition, ExpansionMode ExpansionMode, Axis Axes)
    {
        internal GenerationParameters GenerationParameters => new()
        {
            count = NodeCount,
            size = NodeSize,
            startPoint = StartPosition,
        };
    }

    public record WFCNode(Vector3 Position, LevelGenerationDirection Direction)
    {
    }
}
