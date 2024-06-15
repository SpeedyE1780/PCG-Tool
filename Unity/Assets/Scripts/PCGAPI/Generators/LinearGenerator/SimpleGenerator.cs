using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "Simple Generator", menuName = "Scriptable Objects/PCG/Simple Generator")]
    public class SimpleGenerator : LinearGenerator
    {
        [SerializeField]
        private PCGEngine.Axis axis;
        [SerializeField]
        private PCGEngine.Direction direction;

        protected override void GenerateWithEngine(ref PCGEngine.GenerationParameters parameters)
        {
            PCGEngine.SimpleGenerator(ref parameters, axis, direction, AddSpawnPoint);
        }
    }
}
