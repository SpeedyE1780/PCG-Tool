using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    [CreateAssetMenu(menuName = "Scriptable Objects/PCG/SequenceNode")]
    public class SequenceNodeSO : ScriptableObject, ISequenceNode
    {
        [SerializeField]
        private List<SequenceNodeSO> nextNodes;

        public IEnumerable<ISequenceNode> NextNodes => nextNodes;
    }
}
