﻿namespace PCGAPI.WebAPI
{
    public record MultiDimensionParameters(uint NodeCount, float NodeSize, Vector3 StartPosition, Axis Axes, bool DisableOverlap)
    {
        public GenerationParameters GetGenerationParameters() => new()
        {
            count = NodeCount,
            size = NodeSize,
            startPoint = Vector3Helper.ToEngine(StartPosition),
        };
    }
}
