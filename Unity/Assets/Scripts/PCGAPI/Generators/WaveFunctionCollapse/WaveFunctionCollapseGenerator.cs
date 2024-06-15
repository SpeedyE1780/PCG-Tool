using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "WaveFunctionCollapse", menuName = "Scriptable Objects/PCG/Wave Function Collapse Generator")]
    public class WaveFunctionCollapseGenerator : Generator<WFCNode>
    {
        [SerializeField]
        private PCGEngine.Axis axis;
        [SerializeField]
        private PCGEngine.ExpansionMode mode;

        readonly List<int> neighbours = new List<int>();
        int currentIndex = 0;

        private void AddPoint(PCGEngine.Vector3 position, int neighbour)
        {
            AddSpawnPoint(position);
            neighbours.Add(neighbour);
        }

        protected override WFCNode SpawnThing(Vector3 position)
        {
            var node = base.SpawnThing(position);
            int n = neighbours[currentIndex];
            node.SetNeighbors(n);
            currentIndex++;
            return node;
        }

        protected override void GenerateWithEngine(ref PCGEngine.GenerationParameters parameters)
        {
            neighbours.Clear();
            currentIndex = 0;
            PCGEngine.WaveFunctionCollapse(ref parameters, mode, axis, AddPoint);
        }
    }
}
