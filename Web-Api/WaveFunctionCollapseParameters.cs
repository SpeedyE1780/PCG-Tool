namespace PCGAPI.WebAPI
{
    public record WaveFunctionCollapseParameters(uint NodeCount, float NodeSize, Vector3 StartPosition, ExpansionMode ExpansionMode, Axis Axes)
    {
        internal GenerationParameters GenerationParameters => new()
        {
            count = NodeCount,
            size = NodeSize,
            startPoint = VectorHelper.ToEngine(StartPosition),
        };
    }

    public record WFCNode(Vector3 Position, LevelGenerationDirection Direction)
    {
    }

    public record WFC4DNode(Vector4 Position, LevelGenerationDirection Direction)
    {
    }
}
