using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "Generator3D", menuName = "Scriptable Objects/PCG/Generator3D")]
    public class Generator3D : Generator<GameObject>
    {
        [SerializeField]
        private bool disableOverlap;

        protected override void GenerateWithEngine(ref PCGEngine.GenerationParameters parameters)
        {
            PCGEngine.Generator3D(ref parameters, disableOverlap, AddSpawnPoint);
        }
    }
}
