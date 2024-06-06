using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "SimpleGenerator", menuName = "Scriptable Objects/PCG/SimpleGenerator")]
public class SimpleGenerator : Generator
{
    public enum Axis
    {
        x = 0,
        y = 1,
        z = 2
    }

    public enum Direction
    {
        positive = 0,
        negative = 1
    }

    [SerializeField]
    private Axis axis;
    [SerializeField]
    private Direction direction;

    private Vector3 GetDirection()
    {
        return axis switch
        {
            Axis.x => direction == Direction.positive ? Vector3.right : Vector3.left,
            Axis.y => direction == Direction.positive ? Vector3.up : Vector3.down,
            Axis.z => direction == Direction.positive ? Vector3.forward : Vector3.back,
            _ => Vector3.zero,
        };
    }

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
