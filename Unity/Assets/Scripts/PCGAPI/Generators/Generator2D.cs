using System.Collections;
using System.Collections.Generic;
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

        public override IEnumerator Generate(GeneratorData data, Spawn spawnFunction)
        {
            List<Vector3> points = new List<Vector3>();

            PCGEngine.GenerationParameters parameters = PCGEngine2Unity.GeneratorDataToPCGEngineGenerationParameters(data);

            PCGEngine.Generator2D(ref parameters, plane, disableOverlap, (vector) =>
            {
                points.Add(PCGEngine2Unity.PCGEngineVectorToUnity(vector));
            });

            foreach (Vector3 point in points)
            {
                spawnFunction(point);
                yield return null;
            }
        }
    }
}
