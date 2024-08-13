using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    /// <summary>
    /// SequenceNode is a SO can be added to a list of nodes that form a sequence
    /// </summary>
    [CreateAssetMenu(menuName = "Scriptable Objects/PCG/SequenceNode")]
    public class SequenceNode : ScriptableObject, ISequenceNode
    {
        [SerializeField, Tooltip("List of possible next nodes")]
        private List<SequenceNode> nextNodes;

        public IEnumerable<ISequenceNode> NextNodes => nextNodes;

        public int NextCount => nextNodes.Count;
    }
}
