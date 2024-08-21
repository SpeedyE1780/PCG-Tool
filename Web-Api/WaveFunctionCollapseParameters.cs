namespace PCGAPI.WebAPI
{
    public record WaveFunctionCollapseParameters(uint NodeCount, float NodeSize, Vector3 StartPosition, ExpansionMode ExpansionMode, Axis Axes)
    {
        public GenerationParameters GetGenerationParameters() => new()
        {
            count = NodeCount,
            size = NodeSize,
            startPoint = Vector3Helper.ToEngine(StartPosition),
        };
    }

    public record WFCNode(Vector3 Position, LevelGenerationDirection Direction)
    {
    }
}
