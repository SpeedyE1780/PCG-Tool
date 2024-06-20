using UnityEngine;

namespace PCGAPI.Generators
{
    public class GeneratorData
    {
        public readonly uint limit;
        public readonly float size;
        public readonly UnityEngine.Vector3 startPosition;

        public GeneratorData(uint limit, float size, UnityEngine.Vector3 startPosition)
        {
            this.limit = limit;
            this.size = size;
            this.startPosition = startPosition;
        }
    }
}
