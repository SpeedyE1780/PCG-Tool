using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "Generator3D", menuName = "Scriptable Objects/PCG/Generator3D")]
public class Generator3D : Generator
{
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

        PCGEngine2Unity.Generator3D(ref generator, disableOverlap, (vector) =>
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
