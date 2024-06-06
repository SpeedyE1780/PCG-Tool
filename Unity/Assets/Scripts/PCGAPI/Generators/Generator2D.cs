using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Generators
{
    [CreateAssetMenu(fileName = "2DGenerator", menuName = "Scriptable Objects/PCG/2DGenerator")]
    public class Generator2D : Generator
    {
        [SerializeField]
        private PCGEngine2Unity.Plane plane;
        [SerializeField]
        private bool disableOverlap;

        public override IEnumerator Generate(GeneratorData data)
        {
            List<Vector3> points = new List<Vector3>();

            PCGEngine2Unity.GeneratorData generator = new PCGEngine2Unity.GeneratorData()
            {
                limit = data.limit,
                size = data.size,
                startPoint = PCGEngine2Unity.Unity2PCGEngineVector(data.startPosition)
            };

            PCGEngine2Unity.Generator2D(ref generator, plane, disableOverlap, (vector) =>
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
