using UnityEngine;

namespace PCGAPI.Demo
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

        private static bool HasNeighbour(MazeDirection current, MazeDirection direction)
        {
            return (current & direction) > 0;
        }

        public void SetAdjacentNodes(MazeDirection adjacentNodes)
        {
            right.SetActive(!HasNeighbour(adjacentNodes, MazeDirection.right));
            left.SetActive(!HasNeighbour(adjacentNodes, MazeDirection.left));
            backward.SetActive(!HasNeighbour(adjacentNodes, MazeDirection.backward));
            forward.SetActive(!HasNeighbour(adjacentNodes, MazeDirection.forward));
        }
    }
}
