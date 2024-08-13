using UnityEngine;

namespace PCGAPI.Demo
{
    /// <summary>
    /// Class representing a node in generated mazes
    /// </summary>
    public class MazeNode : MonoBehaviour, IMazeNode
    {
        [SerializeField, Tooltip("Right Wall")]
        private GameObject right;
        [SerializeField, Tooltip("Left Wall")]
        private GameObject left;
        [SerializeField, Tooltip("Forward Wall")]
        private GameObject forward;
        [SerializeField, Tooltip("Backward Wall")]
        private GameObject backward;

        /// <summary>
        /// Toggle node's Wall/Stair
        /// </summary>
        /// <param name="adjacentNodes">Adjacent Nodes bit mask</param>
        public void SetAdjacentNodes(MazeDirection adjacentNodes)
        {
            right.SetActive(!adjacentNodes.HasFlag(MazeDirection.right));
            left.SetActive(!adjacentNodes.HasFlag(MazeDirection.left));
            backward.SetActive(!adjacentNodes.HasFlag(MazeDirection.backward));
            forward.SetActive(!adjacentNodes.HasFlag(MazeDirection.forward));
        }
    }
}
