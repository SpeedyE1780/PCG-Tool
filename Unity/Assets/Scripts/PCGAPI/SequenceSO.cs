using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    [CreateAssetMenu(menuName = "Scriptable Objects/PCG/SequenceSO")]
    public class SequenceSO : ScriptableObject
    {
        [SerializeField]
        List<SequenceNodeSO> sequence = new List<SequenceNodeSO>();

        public void AddNode(ISequenceNode node)
        {
            SequenceNodeSO sequenceNode = node as SequenceNodeSO;

            if (sequenceNode == null)
            {
                Debug.LogError("Can't convert ISequenceNode to SequenceNodeSO", this);
                return;
            }

            sequence.Add(sequenceNode);
        }
    }
}
