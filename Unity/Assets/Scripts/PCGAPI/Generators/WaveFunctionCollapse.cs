using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "WaveFunctionCollapse", menuName = "Scriptable Objects/PCG/WaveFunctionCollapse")]
    public class WaveFunctionCollapse : Generator
    {
        protected override void GenerateWithEngine(ref PCGEngine.GenerationParameters parameters)
        {
            PCGEngine.WaveFunctionCollapse(ref parameters, AddSpawnPoint);
        }
    }
}
