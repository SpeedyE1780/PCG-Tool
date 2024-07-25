using System.Collections.Generic;
using System.Linq;

namespace PCGAPI
{
    public interface ISequenceNode
    {
        IEnumerable<ISequenceNode> NextNodes { get; }

        SequenceNode ToSequenceNode() => new SequenceNode() { possibilitiesCount = NextNodes.Count() };
    }
}
