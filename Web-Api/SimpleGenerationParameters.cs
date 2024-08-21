namespace PCGAPI.WebAPI
{
    public record SimpleGenerationParameters(uint NodeCount, float NodeSize, Vector3 StartPosition, Axis Axes)
    {
        internal GenerationParameters GenerationParameters => new()
        {
            count = NodeCount,
            size = NodeSize,
            startPoint = StartPosition,
        };
    }
}
