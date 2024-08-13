using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    [CreateAssetMenu(menuName = "Scriptable Objects/PCG/Sequence")]
    public class Sequence : ScriptableObject
    {
        [SerializeField]
        List<SequenceNode> sequence = new List<SequenceNode>();

        public void AddNode(ISequenceNode node)
        {
            SequenceNode sequenceNode = node as SequenceNode;

            if (sequenceNode == null)
            {
                Debug.LogError("Can't convert ISequenceNode to SequenceNode", this);
                return;
            }

            sequence.Add(sequenceNode);
        }
    }
}
