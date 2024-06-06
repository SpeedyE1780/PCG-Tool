using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "2DGenerator", menuName = "Scriptable Objects/PCG/2DGenerator")]
    public class Generator2D : Generator
    {
        [SerializeField]
        private PCGEngine.Plane plane;
        [SerializeField]
        private bool disableOverlap;

        protected override void GenerateWithEngine(ref PCGEngine.GenerationParameters parameters)
        {
            PCGEngine.Generator2D(ref parameters, plane, disableOverlap, AddSpawnPoint);
        }
    }
}
