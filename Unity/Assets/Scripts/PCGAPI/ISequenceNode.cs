using System.Collections.Generic;
using System.Linq;

namespace PCGAPI
{
    public interface ISequenceNode
    {
        IEnumerable<ISequenceNode> NextNodes { get; }
        ISequenceNode NextNode { get; set; }

        void GenerateSequence(List<SequenceNode> nodes, SequenceNode sequenceNode)
        {
            if (sequenceNode.nextNodeIndex == -1)
            {
                return;
            }

            NextNode = NextNodes.ElementAt(sequenceNode.nextNodeIndex);
            NextNode.GenerateSequence(nodes, nodes[sequenceNode.nextNodes[sequenceNode.nextNodeIndex]]);
        }
    }
}
