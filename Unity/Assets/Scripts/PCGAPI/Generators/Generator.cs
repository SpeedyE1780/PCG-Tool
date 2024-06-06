using System.Collections;
using UnityEngine;

namespace PCGAPI.Generators
{
    public abstract class Generator : ScriptableObject
    {
        public delegate void Spawn(Vector3 position);

        public abstract IEnumerator Generate(GeneratorData data, Spawn spawnFunction);
    }
}
