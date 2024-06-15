using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "Multi Dimension Generator", menuName = "Scriptable Objects/PCG/Multi Dimension Generator")]
    public class MultiDimensionGenerator : LinearGenerator
    {
        [SerializeField]
        private PCGEngine.Axis axis;
        [SerializeField]
        private bool disableOverlap;

        protected override void GenerateWithEngine(ref PCGEngine.GenerationParameters parameters)
        {
            PCGEngine.MultiDimensionGenerator(ref parameters, axis, disableOverlap, AddSpawnPoint);
        }
    }
}
