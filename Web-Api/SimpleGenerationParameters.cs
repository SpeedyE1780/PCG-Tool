namespace PCGAPI.WebAPI
{
    public record SimpleGenerationParameters(uint NodeCount, float NodeSize, Vector3 StartPosition, Vector3 Offset)
    {
        internal GenerationParameters GenerationParameters => new()
        {
            count = NodeCount,
            size = NodeSize,
            startPoint = Vector3Helper.ToEngine(StartPosition),
        };
    }
}
