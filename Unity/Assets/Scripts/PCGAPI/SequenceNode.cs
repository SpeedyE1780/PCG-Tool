using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    [CreateAssetMenu(menuName = "Scriptable Objects/PCG/SequenceNode")]
    public class SequenceNode : ScriptableObject, ISequenceNode
    {
        [SerializeField]
        private List<SequenceNode> nextNodes;

        public IEnumerable<ISequenceNode> NextNodes => nextNodes;

        public int NextCount => nextNodes.Count;
    }
}
