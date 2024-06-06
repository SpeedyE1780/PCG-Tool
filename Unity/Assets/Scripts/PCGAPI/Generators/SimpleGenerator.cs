using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "SimpleGenerator", menuName = "Scriptable Objects/PCG/SimpleGenerator")]
    public class SimpleGenerator : Generator
    {
        [SerializeField]
        private PCGEngine2Unity.Axis axis;
        [SerializeField]
        private PCGEngine2Unity.Direction direction;

        public override IEnumerator Generate(GeneratorData data)
        {
            List<Vector3> points = new List<Vector3>();

            PCGEngine2Unity.GeneratorData generator = new PCGEngine2Unity.GeneratorData()
            {
                limit = data.limit,
                size = data.size,
                startPoint = PCGEngine2Unity.Unity2PCGEngineVector(data.startPosition)
            };

            PCGEngine2Unity.SimpleGenerator(ref generator, axis, direction, (vector) =>
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
