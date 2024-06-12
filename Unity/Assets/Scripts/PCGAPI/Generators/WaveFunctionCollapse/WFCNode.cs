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

        private enum Neighbors
        {
            left = 1 << 0,
            right = 1 << 1,
            forward = 1 << 2,
            backward = 1 << 3,
            up = 1 << 4,
            down = 1 << 5
        };

        private static bool HasNeighbour(int neighbor, Neighbors neighbors)
        {
            return (neighbor & (int)neighbors) > 0;
        }

        public void SetNeighbors(int neighbors)
        {
            right.SetActive(!HasNeighbour(neighbors, Neighbors.right));
            left.SetActive(!HasNeighbour(neighbors, Neighbors.left));
            backward.SetActive(!HasNeighbour(neighbors, Neighbors.backward));
            forward.SetActive(!HasNeighbour(neighbors, Neighbors.forward));
            up.SetActive(HasNeighbour(neighbors, Neighbors.up));
            down.SetActive(HasNeighbour(neighbors, Neighbors.down));
        }
    }
}
