using UnityEngine;

namespace PCGAPI.Generators
{
    public class WFCNode : MonoBehaviour
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

        public void SetNeighbors(Direction neighbors)
        {
            right.SetActive(!HasNeighbour(neighbors, Direction.right));
            left.SetActive(!HasNeighbour(neighbors, Direction.left));
            backward.SetActive(!HasNeighbour(neighbors, Direction.backward));
            forward.SetActive(!HasNeighbour(neighbors, Direction.forward));
            up.SetActive(HasNeighbour(neighbors, Direction.up));
            down.SetActive(HasNeighbour(neighbors, Direction.down));
        }
    }
}
