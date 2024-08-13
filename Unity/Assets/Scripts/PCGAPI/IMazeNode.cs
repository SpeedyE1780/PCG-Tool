using UnityEngine;

namespace PCGAPI
{
    /// <summary>
    /// IMazeNode is used with Maze Generation Window
    /// </summary>
    public interface IMazeNode
    {
        Transform transform { get; }
        GameObject gameObject { get; }

        /// <summary>
        /// Set adjacent Walls/Stairs
        /// </summary>
        /// <param name="adjacentNodes"></param>
        void SetAdjacentNodes(MazeDirection adjacentNodes);
    }
}
