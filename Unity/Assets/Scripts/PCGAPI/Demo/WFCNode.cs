using UnityEngine;

namespace PCGAPI.Demo
{
    /// <summary>
    /// Class representing a node in levels generated using wave function collapse
    /// </summary>
    public class WFCNode : MonoBehaviour, IWFCNode
    {
        [SerializeField, Tooltip("Right Wall")]
        private GameObject right;
        [SerializeField, Tooltip("Left Wall")]
        private GameObject left;
        [SerializeField, Tooltip("Forward Wall")]
        private GameObject forward;
        [SerializeField, Tooltip("Backward Wall")]
        private GameObject backward;
        [SerializeField, Tooltip("Upward Stair")]
        private GameObject up;
        [SerializeField, Tooltip("Downward Stair")]
        private GameObject down;

        private static bool HasNeighbour(LevelGenerationDirection current, LevelGenerationDirection direction)
        {
            return (current & direction) > 0;
        }

        /// <summary>
        /// Toggle node's Wall/Stair
        /// </summary>
        /// <param name="adjacentNodes">Adjacent Nodes bit mask</param>
        public void SetAdjacentNodes(LevelGenerationDirection adjacentNodes)
        {
            right.SetActive(!HasNeighbour(adjacentNodes, LevelGenerationDirection.right));
            left.SetActive(!HasNeighbour(adjacentNodes, LevelGenerationDirection.left));
            backward.SetActive(!HasNeighbour(adjacentNodes, LevelGenerationDirection.backward));
            forward.SetActive(!HasNeighbour(adjacentNodes, LevelGenerationDirection.forward));
            up.SetActive(HasNeighbour(adjacentNodes, LevelGenerationDirection.up));
            down.SetActive(HasNeighbour(adjacentNodes, LevelGenerationDirection.down));
        }
    }
}
