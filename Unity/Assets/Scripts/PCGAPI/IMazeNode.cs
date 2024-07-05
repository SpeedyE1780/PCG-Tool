using UnityEngine;

namespace PCGAPI
{
    public interface IMazeNode
    {
        Transform transform { get; }
        GameObject gameObject { get; }

        void SetAdjacentNodes(Direction adjacentNodes);
    }
}
