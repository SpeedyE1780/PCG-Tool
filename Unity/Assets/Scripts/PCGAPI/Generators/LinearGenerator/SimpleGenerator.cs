using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "SimpleGenerator", menuName = "Scriptable Objects/PCG/SimpleGenerator")]
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
