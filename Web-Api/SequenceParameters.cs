
namespace PCGAPI.WebAPI
{
    public record SequenceParameters(SequenceNode Start, List<SequenceNode> Nodes)
    {
    }

    public record CyclicSequenceParameters(SequenceNode Start, List<SequenceNode> Nodes, int SequenceLength)
    {
    }

    public record SequenceNode(int ID, List<int> NextNodes)
    {
    }

    internal class SequenceNodeImplementation : ISequenceNode
    {
        internal SequenceNodeImplementation(int id)
        {
            ID = id;
        }

        public int ID { get; set; } = 0;

        public List<SequenceNodeImplementation> Children { get; set; } = [];

        public IEnumerable<ISequenceNode> NextNodes => Children;

        public int NextCount => Children.Count;
    }
}
