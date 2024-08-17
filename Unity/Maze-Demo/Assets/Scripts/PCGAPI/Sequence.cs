using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    /// <summary>
    /// Sequence is a SO that contains a list of nodes that form a sequence
    /// </summary>
    [CreateAssetMenu(menuName = "Scriptable Objects/PCG/Sequence")]
    public class Sequence : ScriptableObject
    {
        [SerializeField, Tooltip("List of nodes in sequence")]
        private List<SequenceNode> sequence = new List<SequenceNode>();

        /// <summary>
        /// Add a node to sequence
        /// </summary>
        /// <param name="node">Node added to sequence</param>
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
