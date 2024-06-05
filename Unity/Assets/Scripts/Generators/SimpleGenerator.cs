using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "SimpleGenerator", menuName = "Scriptable Objects/PCG/SimpleGenerator")]
public class SimpleGenerator : Generator
{
    private enum Axis
    {
        x,
        y,
        z
    }

    private enum Direction
    {
        positive,
        negative
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

        PCGEngine2Unity.SimpleGenerator((x, y, z) =>
        {
            points.Add(new Vector3(x, y, z));
        });

        foreach (Vector3 point in points)
        {
            SpawnCell(data.cell, point);
            yield return null;
        }
    }
}
