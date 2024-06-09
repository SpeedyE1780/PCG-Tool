using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "WaveFunctionCollapse", menuName = "Scriptable Objects/PCG/WaveFunctionCollapse")]
    public class WaveFunctionCollapse : Generator
    {
        List<int> neighbours = new List<int>();
        int currentIndex = 0;

        private void AddPoint(PCGEngine.Vector3 position, int neighbour)
        {
            AddSpawnPoint(position);
            neighbours.Add(neighbour);
        }

        enum Neighbors
        {
            left = 1 << 0,
            right = 1 << 1,
            forward = 1 << 2,
            backward = 1 << 3,
            up = 1 << 4,
            down = 1 << 5
        };

        private bool HasNeighbour(int neighbour, Neighbors neighbors)
        {
            return (neighbour & (int)neighbors) > 0;
        }

        protected override GameObject SpawnThing(Vector3 position)
        {
            var go = base.SpawnThing(position);

            int n = neighbours[currentIndex];
            currentIndex++;
            go.transform.Find("Right").gameObject.SetActive(HasNeighbour(n, Neighbors.right));
            go.transform.Find("Left").gameObject.SetActive(HasNeighbour(n, Neighbors.left));
            go.transform.Find("Up").gameObject.SetActive(HasNeighbour(n, Neighbors.up));
            go.transform.Find("Down").gameObject.SetActive(HasNeighbour(n, Neighbors.down));
            go.transform.Find("Backward").gameObject.SetActive(HasNeighbour(n, Neighbors.backward));
            go.transform.Find("Forward").gameObject.SetActive(HasNeighbour(n, Neighbors.up));

            return go;
        }

        protected override void GenerateWithEngine(ref PCGEngine.GenerationParameters parameters)
        {
            neighbours.Clear();
            currentIndex = 0;
            PCGEngine.WaveFunctionCollapse(ref parameters, AddPoint);
        }
    }
}
