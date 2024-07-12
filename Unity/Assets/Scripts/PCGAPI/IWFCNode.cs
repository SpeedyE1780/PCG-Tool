using UnityEngine;

namespace PCGAPI
{
    public interface IWFCNode
    {
        Transform transform { get; }
        GameObject gameObject { get; }

        void SetAdjacentNodes(Direction adjacentNodes);
    }
}
