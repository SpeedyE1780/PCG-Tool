using System.Collections.Generic;

namespace PCGAPI
{
    public interface ISequenceNode
    {
        IEnumerable<ISequenceNode> NextNodes { get; }
        ISequenceNode NextNode { get; set; }
    }
}
