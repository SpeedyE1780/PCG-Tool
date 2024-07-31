using UnityEngine;

namespace PCGAPI
{
    public class WFCNode : MonoBehaviour, IWFCNode
    {
        [SerializeField]
        private GameObject right;
        [SerializeField]
        private GameObject left;
        [SerializeField]
        private GameObject forward;
        [SerializeField]
        private GameObject backward;
        [SerializeField]
        private GameObject up;
        [SerializeField]
        private GameObject down;

        private static bool HasNeighbour(LevelGenerationDirection current, LevelGenerationDirection direction)
        {
            return (current & direction) > 0;
        }

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
