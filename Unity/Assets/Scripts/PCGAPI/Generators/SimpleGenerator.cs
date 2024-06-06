using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "SimpleGenerator", menuName = "Scriptable Objects/PCG/SimpleGenerator")]
    public class SimpleGenerator : Generator
    {
        [SerializeField]
        private PCGEngine.Axis axis;
        [SerializeField]
        private PCGEngine.Direction direction;

        public override IEnumerator Generate(GeneratorData data)
        {
            List<Vector3> points = new List<Vector3>();

            PCGEngine.GenerationParameters parameters = PCGEngine2Unity.GeneratorDataToPCGEngineGenerationParameters(data);

            PCGEngine.SimpleGenerator(ref parameters, axis, direction, (vector) =>
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
