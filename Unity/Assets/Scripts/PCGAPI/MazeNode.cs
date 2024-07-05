using UnityEngine;

namespace PCGAPI
{
    public class MazeNode : MonoBehaviour, IMazeNode
    {
        [SerializeField]
        private GameObject right;
        [SerializeField]
        private GameObject left;
        [SerializeField]
        private GameObject forward;
        [SerializeField]
        private GameObject backward;

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
        }
    }
}
