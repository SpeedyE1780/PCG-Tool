namespace PCGAPI.WebAPI
{
    public record SimpleGenerationParameters(uint NodeCount, float NodeSize, Vector3 StartPosition, Axis Axes)
    {
        public GenerationParameters GetGenerationParameters() => new()
        {
            count = NodeCount,
            size = NodeSize,
            startPoint = Vector3Helper.ToEngine(StartPosition),
        };
    }
}
