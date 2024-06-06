using UnityEngine;

namespace PCGAPI
{
    public class GeneratorData
    {
        public readonly GameObject cell;
        public readonly uint limit;
        public readonly float size;
        public readonly Vector3 startPosition;

        public GeneratorData(GameObject cell, uint limit, float size, Vector3 startPosition)
        {
            this.cell = cell;
            this.limit = limit;
            this.size = size;
            this.startPosition = startPosition;
        }
    }
}
