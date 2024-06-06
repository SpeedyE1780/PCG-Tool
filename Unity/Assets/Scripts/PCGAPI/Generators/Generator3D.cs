using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "Generator3D", menuName = "Scriptable Objects/PCG/Generator3D")]
    public class Generator3D : Generator
    {
        [SerializeField]
        private bool disableOverlap;

        public override IEnumerator Generate(GeneratorData data)
        {
            List<Vector3> points = new List<Vector3>();

            PCGEngine.GenerationParameters parameters = PCGEngine2Unity.GeneratorDataToPCGEngineGenerationParameters(data);

            PCGEngine.Generator3D(ref parameters, disableOverlap, (vector) =>
            {
                points.Add(PCGEngine2Unity.PCGEngineVectorToUnity(vector));
            });

            foreach (Vector3 point in points)
            {
                SpawnCell(data.cell, point);
                yield return null;
            }
        }
    }
}
