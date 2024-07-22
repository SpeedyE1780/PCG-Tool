using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    [CreateAssetMenu(menuName = "Scriptable Objects/PCG/SequenceNode")]
    public class SequenceNodeSO : ScriptableObject, ISequenceNode
    {
        [SerializeField]
        private List<SequenceNodeSO> nextNodes;
        [SerializeField]
        private SequenceNodeSO nextNode;

        public IEnumerable<ISequenceNode> NextNodes => nextNodes;
        public ISequenceNode NextNode { get => nextNode; set => nextNode = (SequenceNodeSO)value; }
    }
}
