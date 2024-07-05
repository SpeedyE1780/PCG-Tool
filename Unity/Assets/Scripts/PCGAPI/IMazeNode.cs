using UnityEngine;

namespace PCGAPI
{
    public interface IMazeNode
    {
        Transform transform { get; }
        void SetAdjacentNodes(Direction adjacentNodes);
    }
}
