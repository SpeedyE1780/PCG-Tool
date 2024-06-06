using UnityEngine;

namespace PCGAPI
{
    public class GeneratorData
    {
        public readonly uint limit;
        public readonly float size;
        public readonly Vector3 startPosition;

        public GeneratorData(uint limit, float size, Vector3 startPosition)
        {
            this.limit = limit;
            this.size = size;
            this.startPosition = startPosition;
        }
    }
}
