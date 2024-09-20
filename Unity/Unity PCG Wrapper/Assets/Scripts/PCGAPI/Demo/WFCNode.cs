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
        [SerializeField, Tooltip("Portal In")]
        private GameObject portalIn;
        [SerializeField, Tooltip("Portal Out")]
        private GameObject portalOut;

        /// <summary>
        /// Toggle node's Wall/Stair
        /// </summary>
        /// <param name="adjacentNodes">Adjacent Nodes bit mask</param>
        public void SetAdjacentNodes(LevelGenerationDirection adjacentNodes)
        {
            right.SetActive(!adjacentNodes.HasFlag(LevelGenerationDirection.right));
            left.SetActive(!adjacentNodes.HasFlag(LevelGenerationDirection.left));
            backward.SetActive(!adjacentNodes.HasFlag(LevelGenerationDirection.backward));
            forward.SetActive(!adjacentNodes.HasFlag(LevelGenerationDirection.forward));
            up.SetActive(adjacentNodes.HasFlag(LevelGenerationDirection.up));
            down.SetActive(adjacentNodes.HasFlag(LevelGenerationDirection.down));
            portalIn.SetActive(adjacentNodes.HasFlag(LevelGenerationDirection.portalIn));
            portalOut.SetActive(adjacentNodes.HasFlag(LevelGenerationDirection.portalOut));
        }
    }
}
