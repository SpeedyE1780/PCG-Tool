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

        private static bool HasNeighbour(Direction current, Direction direction)
        {
            return (current & direction) > 0;
        }

        public void SetAdjacentNodes(Direction adjacentNodes)
        {
            right.SetActive(!HasNeighbour(adjacentNodes, Direction.right));
            left.SetActive(!HasNeighbour(adjacentNodes, Direction.left));
            backward.SetActive(!HasNeighbour(adjacentNodes, Direction.backward));
            forward.SetActive(!HasNeighbour(adjacentNodes, Direction.forward));
            up.SetActive(HasNeighbour(adjacentNodes, Direction.up));
            down.SetActive(HasNeighbour(adjacentNodes, Direction.down));
        }
    }
}
