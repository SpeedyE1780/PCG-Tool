using System.Collections.Generic;
using System.Linq;

namespace PCGAPI
{
    public interface ISequenceNode
    {
        IEnumerable<ISequenceNode> NextNodes { get; }
        ISequenceNode NextNode { get; set; }

        SequenceNode ToSequenceNode()
        {
            var node = new SequenceNode();

            node.nextCount = NextNodes.Count();
            node.nextNodes = new SequenceNode[node.nextCount];

            int index = 0;

            foreach (ISequenceNode sequenceNode in NextNodes)
            {
                node.nextNodes[index] = sequenceNode.ToSequenceNode();
                index += 1;
            }

            return node;
        }

        void GenerateSequence(SequenceNode sequenceNode)
        {
            if (sequenceNode.nextNodeIndex == -1)
            {
                return;
            }

            NextNode = NextNodes.ElementAt(sequenceNode.nextNodeIndex);
            NextNode.GenerateSequence(sequenceNode.nextNodes[sequenceNode.nextNodeIndex]);
        }
    }
}
